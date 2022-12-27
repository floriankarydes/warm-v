#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"
#include "opencv2/xfeatures2d.hpp"

#include <iostream>

using namespace std;
using namespace cv;

bool divide_images = false;
Stitcher::Mode mode = Stitcher::PANORAMA;
vector<Mat> imgs;
string result_name = "result.jpg";

void printUsage(char** argv);
int parseCmdArgs(int argc, char** argv);

int main(int argc, char* argv[])
{
	int retval = parseCmdArgs(argc, argv);
	if (retval) return EXIT_FAILURE;

	Mat pano;
	Ptr<Stitcher> stitcher = makePtr<Stitcher>();



	// CONFIGURE REGISTRATION

	// Resize to medium resolution
	stitcher->setRegistrationResol(0.6);

	// Find features
	stitcher->setFeaturesFinder(xfeatures2d::SURF::create());

	// Match features
	stitcher->setFeaturesMatcher(makePtr<detail::BestOf2NearestMatcher>(false, 0.3));

	// Estimate cameras parameters
	stitcher->setEstimator(makePtr<detail::HomographyBasedEstimator>());

	// Refine cameras parameters
	stitcher->setPanoConfidenceThresh(0.3);
	stitcher->setBundleAdjuster(makePtr<detail::BundleAdjusterRay>()); //! FAIL

	// Apply wave correction to cameras parameters
	stitcher->setWaveCorrection(true);
	stitcher->setWaveCorrectKind(detail::WAVE_CORRECT_HORIZ);


	// CONFIGURE COMPOSITING

	// Resize to low resolution
	stitcher->setSeamEstimationResol(0.1);

	// Wrap image
	stitcher->setWarper(makePtr<SphericalWarper>());
	stitcher->setInterpolationFlags(INTER_LINEAR);

	// Compensate exposure
	stitcher->setExposureCompensator(makePtr<detail::BlocksGainCompensator>());

	// Find seams
	stitcher->setSeamFinder(makePtr<detail::GraphCutSeamFinder>(detail::GraphCutSeamFinderBase::COST_COLOR));

	// Compositing pano
	stitcher->setCompositingResol(cv::Stitcher::ORIG_RESOL);
	stitcher->setBlender(makePtr<detail::MultiBandBlender>(false));



	Stitcher::Status status = stitcher->stitch(imgs, pano);

	if (status != Stitcher::OK)
	{
			cout << "Can't stitch images, error code = " << int(status) << endl;
			return EXIT_FAILURE;
	}

	imwrite(result_name, pano);
	cout << "stitching completed successfully\n" << result_name << " saved!";
	return EXIT_SUCCESS;
}


void printUsage(char** argv)
{
	cout <<
		"Images stitcher.\n\n" << "Usage :\n" << argv[0] <<" [Flags] img1 img2 [...imgN]\n\n"
		"Flags:\n"
		"  --d3\n"
		"      internally creates three chunks of each image to increase stitching success\n"
		"  --mode (panorama|scans)\n"
		"      Determines configuration of stitcher. The default is 'panorama',\n"
		"      mode suitable for creating photo panoramas. Option 'scans' is suitable\n"
		"      for stitching materials under affine transformation, such as scans.\n"
		"  --output <result_img>\n"
		"      The default is 'result.jpg'.\n\n"
		"Example usage :\n" << argv[0] << " --d3 --mode scans img1.jpg img2.jpg\n";
}


int parseCmdArgs(int argc, char** argv)
{
	if (argc == 1)
	{
		printUsage(argv);
		return EXIT_FAILURE;
	}

	for (int i = 1; i < argc; ++i)
	{
		if (string(argv[i]) == "--help" || string(argv[i]) == "/?")
		{
			printUsage(argv);
			return EXIT_FAILURE;
		}
		else if (string(argv[i]) == "--d3")
		{
			divide_images = true;
		}
		else if (string(argv[i]) == "--output")
		{
			result_name = argv[i + 1];
			i++;
		}
		else if (string(argv[i]) == "--mode")
		{
			if (string(argv[i + 1]) == "panorama")
				mode = Stitcher::PANORAMA;
			else if (string(argv[i + 1]) == "scans")
				mode = Stitcher::SCANS;
			else
			{
				cout << "Bad --mode flag value\n";
				return EXIT_FAILURE;
			}
			i++;
		}
		else
		{
			Mat img = imread(samples::findFile(argv[i]));
			if (img.empty())
			{
				cout << "Can't read image '" << argv[i] << "'\n";
				return EXIT_FAILURE;
			}

			if (divide_images)
			{
				Rect rect(0, 0, img.cols / 2, img.rows);
				imgs.push_back(img(rect).clone());
				rect.x = img.cols / 3;
				imgs.push_back(img(rect).clone());
				rect.x = img.cols / 2;
				imgs.push_back(img(rect).clone());
			}
			else
					imgs.push_back(img);
		}
	}
	return EXIT_SUCCESS;
}

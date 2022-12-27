#!/usr/bin/env bash

REPO_DIR="$(dirname "$(cd -- "$(dirname -- "$0")" && pwd -P)" )"

BIN_PATH="${REPO_DIR}/build/bin"
INPUT_DIR="${REPO_DIR}/data/inputs/cropsy/stitching"
OUTPUT_DIR="${REPO_DIR}/data/outputs"
IMG_NAME="398"

"${BIN_PATH}/stitching_detailed" ${INPUT_DIR}/${IMG_NAME}* \
	--output "${OUTPUT_DIR}/stitching_${IMG_NAME}.jpeg" \
	--try_cuda yes \
	--work_megapix 0.6 \
	--features surf \
	--matcher homography \
	--estimator homography \
	--match_conf 0.65 \
	--conf_thresh 1.0 \
	--ba ray \
	--ba_refine_mask xxxxx \
	--wave_correct horiz \
	--save_graph "${OUTPUT_DIR}/stitching_${IMG_NAME}.dot" \
	--warp spherical \
	--seam_megapix 0.1 \
	--seam gc_color \
	--compose_megapix -1 \
	--expos_comp gain_blocks \
	--expos_comp_nr_feeds 1 \
	--expos_comp_nr_filtering 2 \
	--expos_comp_block_size 32 \
	--blend multiband \
	--blend_strength 5
	# --rangewidth 2

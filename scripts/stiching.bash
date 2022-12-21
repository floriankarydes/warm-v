#!/usr/bin/env bash

REPO_DIR="$(dirname "$(cd -- "$(dirname -- "$0")" && pwd -P)" )"

BIN_PATH="${REPO_DIR}/build/bin"
INPUT_DIR="${REPO_DIR}/data/inputs/opencv/stitching"
OUTPUT_DIR="${REPO_DIR}/data/outputs"
IMG_NAME="boat"

"${BIN_PATH}/stitching" --mode panorama --output "${OUTPUT_DIR}/stitching_${IMG_NAME}.jpeg" ${INPUT_DIR}/${IMG_NAME}*

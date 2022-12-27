#!/usr/bin/env bash

REPO_DIR="$(dirname "$(cd -- "$(dirname -- "$0")" && pwd -P)" )"

BIN_PATH="${REPO_DIR}/build/bin"
INPUT_DIR="${REPO_DIR}/data/inputs"
OUTPUT_DIR="${REPO_DIR}/data/outputs"
OUTPUT_NAME="stitching_result"

"${BIN_PATH}/stitching_custom" --output "${OUTPUT_DIR}/${OUTPUT_NAME}.jpeg" ${INPUT_DIR}/*

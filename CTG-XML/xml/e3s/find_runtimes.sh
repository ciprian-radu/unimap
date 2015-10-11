#!/bin/bash

echo "This script prints the value of the runtime attribute from the mapping XML files."
echo "usage: ./find_runtimes.sh apcg_id mapping_id"

APCG_ID=$1
MAPPING_ID=$2

for xml in $(find -name mapping*_${APCG_ID}_${MAPPING_ID}.xml)
do
	echo -e "${xml}\t`grep runtime $xml | cut -d'"' -f 2`"
done | sort

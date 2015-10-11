#!/bin/sh

XSDS="core task ctg apcg mapping"
OUTPUT_FOLDER="src/ro/ulbsibiu/acaps/ctg/xml/"
SCHEMA_FOLDER="src/ro/ulbsibiu/acaps/ctg/xml/schema/"

echo "Creating C++ code based on the XSDs"

for XSD in $XSDS
do
	xsd cxx-tree --generate-serialization --generate-doxygen --output-dir ${OUTPUT_FOLDER}/${XSD} ${SCHEMA_FOLDER}/${XSD}.xsd
done

echo "Done."

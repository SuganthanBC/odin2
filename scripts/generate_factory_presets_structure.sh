#!/bin/bash

# This file generates cpp code that tells the patch browser the tree structure of how factory presets are named

CPP_FILE="../Source/gui/FactoryPresetNames.h"
CPP_FILE_ABS=$(realpath "$CPP_FILE")
FP_DIR="../Soundbanks/Factory Presets"
echo $FP_DIR_ABS

echo "// This file is automatically generated by odin2/scripts/generate_factory_presets_structure.sh" > $CPP_FILE_ABS
echo "// If you make changes to the FactoryPresets, you need to run said script again and regerate this file!" >> $CPP_FILE_ABS
echo "" >> $CPP_FILE_ABS

cd "$FP_DIR"
pwd

#generate first vector containing the folder names
echo "std::map<std::string, std::vector<std::string>> m_factory_preset_cat_and_names = {" >> $CPP_FILE_ABS
for cat in *; do
    CATEGORY=$(realpath --relative-to=. "$cat")
    echo "Category folder: $CATEGORY"
    echo "    { \"$CATEGORY\", " >> $CPP_FILE_ABS
    echo "    {" >> $CPP_FILE_ABS
    cd "$cat"
    # write individual preset names:
    for preset in *; do
        echo "        \"$preset\", " >> $CPP_FILE_ABS

    done
    cd ..
    echo "    } }," >> $CPP_FILE_ABS
    echo ""
done
echo "};" >> $CPP_FILE_ABS
echo "" >> $CPP_FILE_ABS

#generate all the vectors containing the preset names for their respective_folders

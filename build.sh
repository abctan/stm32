#!/bin/bash

print_help()
{
    echo "###############################"
    echo "Building Project Help"
    echo "./build.sh [OPTION] [OPTION]"
    echo "[OPTION] is clean or all"
    echo "example: [./build.sh clean]; [./build.sh all]; [./build.sh clean all]"
    echo "###############################"
}

compile_project()
{
    para_num=$1
    para_opt1=$2
    para_opt2=$3
    bulid_opt=("clean" "all")

    if [[ ${para_num} -eq 0 || ${para_num} -gt 2 ]]
    then
        print_help
        exit 0
    else
        if [[ ${para_num} -eq 1 ]]
        then
            if [[ ${para_opt1} != ${bulid_opt[0]} && ${para_opt1} != ${bulid_opt[1]} ]]
            then
                print_help
                exit 0
            fi
        else
            if [[ ${para_opt1} != ${bulid_opt[0]} && ${para_opt2} != ${bulid_opt[1]} ]]
            then
                print_help
                exit 0
            fi
        fi
    fi

    if [[ ${para_opt1} = ${bulid_opt[0]} ]]
    then
        if [[ -d "./build" && -e "./build/Makefile" ]]
        then
            cd ./build
            make clean
            cd ..
            echo "clean project ok!"
        else
            echo "not find Makefile!"
        fi
    fi
    if [[ ${para_opt1} = ${bulid_opt[1]} || ${para_opt2} = ${bulid_opt[1]} ]]
    then
        mkdir -p ./build
        cd ./build
        cmake ..
        make -j
    fi

    exit 0
}

compile_project $# $1 $2
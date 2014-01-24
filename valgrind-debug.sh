#!/bin/bash

valgrind --leak-check=full --track-origins=yes --suppressions=./SI.supp ./build/SI-Debug

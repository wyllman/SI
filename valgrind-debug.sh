#!/bin/bash

valgrind --leak-check=full --track-origins=yes --suppressions=./SI.supp ./Debug/SI

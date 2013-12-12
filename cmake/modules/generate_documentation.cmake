function (GENERATE_DOCUMENTATION DOXYGEN_CONFIG_FILE)

find_package (Doxygen)
set (DOXYFILE_FOUND FALSE)

if (EXISTS ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE})
    set (DOXYFILE_FOUND TRUE)
endif (EXISTS ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE})

if (DOXYGEN_FOUND)
	if (DOXYFILE_FOUND)
		# Add target
		add_custom_target (doc ALL ${DOXYGEN_EXECUTABLE} "$
			{PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE}" )
		# Add .tag file and generated documentation to the list 
		# of files we must erase when distcleaning
		# Read doxygen configuration file
		file (READ ${PROJECT_SOURCE_DIR}/${DOXYGEN_CONFIG_FILE} 
			DOXYFILE_CONTENTS)

		string (REGEX REPLACE "\n" ";" DOXYFILE_LINES ${DOXYFILE_CONTENTS} )
		# Parse .tag filename and add to list of files to delete 
		# if it exists
		foreach (DOXYLINE ${DOXYFILE_CONTENTS})
			string (REGEX REPLACE ".*GENERATE_TAGFILE *= *([^^\n]+).*" "\\1" 
				DOXYGEN_TAG_FILE ${DOXYLINE} )
		endforeach (DOXYLINE)

		add_to_distclean (${PROJECT_BINARY_DIR}/${DOXYGEN_TAG_FILE})
		# Parse doxygen output doc dir and add to list of files 
		# to delete if it exists
		foreach (DOXYLINE ${DOXYFILE_CONTENTS})
			string (REGEX REPLACE ".*OUTPUT_DIRECTORY *= *([^^\n]+).*" "\\1" 
				DOXYGEN_DOC_DIR ${DOXYLINE} )
		endforeach (DOXYLINE)
		add_to_distclean (${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR})
		add_to_distclean (${PROJECT_BINARY_DIR}/${DOXYGEN_DOC_DIR}.dir)
	else (DOXYFILE_FOUND)
		message (STATUS "Doxygen configuration file not found.\n
		­Documentation will not be generated" )
	endif (DOXYFILE_FOUND)
else (DOXYGEN_FOUND)
	message (STATUS "Doxygen not found ­ Documentation will not be generated")
endif (DOXYGEN_FOUND)
endmacro (GENERATE_DOCUMENTATION)
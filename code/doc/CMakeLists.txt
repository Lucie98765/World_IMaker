find_package (Doxygen)

message("World_IMaker_SOURCE_DIR     " ${World_IMaker_SOURCE_DIR})
message("World_IMaker_BINARY_DIR     " ${World_IMaker_BINARY_DIR})
message("DOXYGEN_EXECUTABLE     " ${DOXYGEN_EXECUTABLE})

if(DOXYGEN_FOUND)
  configure_file (${World_IMaker_SOURCE_DIR}/doc/Doxyfile-html.cmake ${World_IMaker_BINARY_DIR}/doc/Doxyfile-html)
  add_custom_target (html ${DOXYGEN_EXECUTABLE} ${World_IMaker_BINARY_DIR}/doc/Doxyfile-html)
endif (DOXYGEN_FOUND)

cmake_minimum_required(VERSION 3.13)

function(load_file_data FILENAME OUTPUT_C_SIZE OUTPUT_C_DATA)
  set(RANDOM_LOGO_FILEPATH ${FILENAME})

  file(READ ${RANDOM_LOGO_FILEPATH} RANDOM_LOGO_DATA_HEX HEX)
  file(SIZE ${RANDOM_LOGO_FILEPATH} INOUTPUT_C_SIZE)

  string(
    REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1, "  
    RANDOM_LOGO_DATA_SINGLELINE ${RANDOM_LOGO_DATA_HEX}
  )

  string(
    REGEX REPLACE
    "(0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f], 0x[0-9a-f][0-9a-f],) "
    "\t\t\\1\n"
    INOUTPUT_C_DATA
    ${RANDOM_LOGO_DATA_SINGLELINE}
  )

  set(${OUTPUT_C_SIZE} ${INOUTPUT_C_SIZE} PARENT_SCOPE)
  set(${OUTPUT_C_DATA} ${INOUTPUT_C_DATA} PARENT_SCOPE)
endfunction()
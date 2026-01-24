#-----------------------------------------------------------------------------------------------------------------------
# to_pascal_case()
#-----------------------------------------------------------------------------------------------------------------------
function(to_pascal_case INPUT_STRING OUTPUT_STRING)
    # Replace common delimiters with spaces
    string(REGEX REPLACE "[_\\-\\.]" " " temp "${INPUT_STRING}")

    # Insert space before uppercase letters in camelCase (but not at start)
    # This regex finds lowercase followed by uppercase and inserts space between
    string(REGEX REPLACE "([a-z])([A-Z])" "\\1 \\2" temp "${temp}")

    # Insert space between consecutive uppercase and lowercase (for acronyms)
    # e.g., "XMLParser" -> "XML Parser"
    string(REGEX REPLACE "([A-Z]+)([A-Z][a-z])" "\\1 \\2" temp "${temp}")

    # Convert to lowercase first for consistent processing
    string(TOLOWER "${temp}" temp)

    # Split into words
    string(REGEX REPLACE " +" ";" word_list "${temp}")

    set(result "")
    foreach(word ${word_list})
        # Skip empty words
        if(word)
            # Capitalize first letter of each word
            string(SUBSTRING "${word}" 0 1 first_char)
            string(TOUPPER "${first_char}" first_char)

            string(LENGTH "${word}" word_len)
            if(word_len GREATER 1)
                string(SUBSTRING "${word}" 1 -1 rest_chars)
                set(word "${first_char}${rest_chars}")
            else()
                set(word "${first_char}")
            endif()

            string(APPEND result "${word}")
        endif()
    endforeach()

    set(${OUTPUT_STRING} "${result}" PARENT_SCOPE)
endfunction()


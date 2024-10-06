#ifndef PARSER_H
#define PARSER_H

#include "balises.h"

/**
 * @brief Parses a .mct file and returns the root balise.
 *
 * This function reads the specified .mct file and constructs a tree of balises
 * representing the structure of the file. The root balise is typically a container
 * balise that contains other nested balises.
 *
 * @param file_path The path to the .mct file to be parsed.
 * @return A pointer to the root balise of the parsed .mct file.
 */
balise_t* parse_mct_file(const char* file_path);

/**
 * @brief Parses a string containing .mct content and returns the root balise.
 *
 * This function takes a string containing .mct formatted content and constructs
 * a tree of balises representing the structure of the content. The root balise
 * is typically a container balise that contains other nested balises.
 *
 * @param content The string containing .mct content to be parsed.
 * @return A pointer to the root balise of the parsed .mct content.
 */
balise_t* parse_mct_string(const char* content);

#endif // PARSER_H

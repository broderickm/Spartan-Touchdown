/**
 * @file ids.h
 * @author Maggie Broderick
 *
 * ID values for the program
 */

#ifndef PROJECT1_IDS_H
#define PROJECT1_IDS_H
#include <wx/defs.h>

/// Types of levels in the game
enum IDs
{
    IDM_LEVELZERO = wxID_HIGHEST + 1,
    IDM_LEVELONE,
    IDM_LEVELTWO,
    IDM_LEVELTHREE
};

#endif //PROJECT1_IDS_H
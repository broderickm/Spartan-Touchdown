#include <pch.h>
#include <gtest/gtest.h>
#include <wx/filefn.h>
#include <wx/image.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}

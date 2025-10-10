#include <pch.h>
#include <gtest/gtest.h>
#include <wx/filefn.h>
#include <wx/image.h>

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    // Suppress PNG color profile warnings
    wxLog::SetLogLevel(wxLOG_Error);

    return RUN_ALL_TESTS();
}

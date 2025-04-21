//
// Created by kolbe on 21.04.2025.
//

#include <stdexcept>
#include <cpplog/common/rotation_file_sink_options.h>

using namespace std;
using namespace cpplog::common;

RotationFileSinkOptions::RotationFileSinkOptions() : FileSinkOptions(), numberOfHistoricalFiles(1),
                                                     maximalFileSize(1024)
{
    this->RotationFileSinkOptions::validate();
}

RotationFileSinkOptions::RotationFileSinkOptions(const size_t historicalFiles,
                                                 const size_t maximalFileSizeInKiloBytes) :
    FileSinkOptions(),
    numberOfHistoricalFiles(historicalFiles), maximalFileSize(maximalFileSizeInKiloBytes)
{
    this->RotationFileSinkOptions::validate();
}

RotationFileSinkOptions::RotationFileSinkOptions(const size_t historicalFiles, const size_t maximalFileSizeInKiloBytes,
                                                 const string& file_name, const string& folder_name,
                                                 const bool clean_on_initialize) :
    FileSinkOptions(file_name, folder_name, clean_on_initialize), numberOfHistoricalFiles(historicalFiles),
    maximalFileSize(maximalFileSizeInKiloBytes)
{
}

void RotationFileSinkOptions::validate()
{
    FileSinkOptions::validate(); // Validate the base class fields.

    if (numberOfHistoricalFiles == 0)
    {
        throw invalid_argument("Number of historical files must be greater than zero.");
    }

    if (maximalFileSize == 0)
    {
        throw invalid_argument("Maximal file size must be greater than zero.");
    }
}

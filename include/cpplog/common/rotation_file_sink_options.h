//
// Created by psp515 on 19.04.2025.
//

#ifndef ROTATION_FILE_SINK_OPTIONS_H
#define ROTATION_FILE_SINK_OPTIONS_H

#include <cpplog/common/file_sink_options.h>

namespace cpplog::common
{
    /// Options class for file sink with rotation.
    class RotationFileSinkOptions : public FileSinkOptions
    {
    public:
        /// Default constructor sets fields to default values.
        RotationFileSinkOptions() : FileSinkOptions(), numberOfHistoricalFiles(1), maximalFileSize(1024)
        {
        }

        ///
        /// Allows setting custom values for number of historical files and maximum file size
        ///
        /// @param historicalFiles Number of historical (rotated) log files to keep.
        /// @param maximalFileSizeInKiloBytes Maximum allowed size of a log file in kilobytes before rotation.
        RotationFileSinkOptions(const size_t historicalFiles, const size_t maximalFileSizeInKiloBytes) :
            FileSinkOptions(),
            numberOfHistoricalFiles(historicalFiles), maximalFileSize(maximalFileSizeInKiloBytes)
        {
        }

        ///
        /// Creates options for rotation file sink, with properties provided by user.
        ///
        /// @param file_name Name of the log file with extnesion.
        /// @param folder_name Name of the folder where logs will be stored.
        /// @param clean_on_initialize Tells when initializing sink, file for logs should be cleaned.
        /// @param historicalFiles Number of historical (rotated) log files to keep.
        /// @param maximalFileSizeInKiloBytes Maximum allowed size of a log file in kilobytes before rotation.
        explicit RotationFileSinkOptions(const size_t historicalFiles, const size_t maximalFileSizeInKiloBytes,
                                const string& file_name, const string& folder_name,
                                const bool clean_on_initialize) :
            FileSinkOptions(file_name, folder_name, clean_on_initialize), numberOfHistoricalFiles(historicalFiles),
            maximalFileSize(maximalFileSizeInKiloBytes)
        {
        }

        ///
        /// Gets the number of historical log files to retain.
        ///
        /// @return Number of historical log files.
        [[nodiscard]] size_t getNumberOfHistoricalFiles() const { return numberOfHistoricalFiles; }

        ///
        /// Gets the maximum size a log file can reach before rotation.
        ///
        /// @return  Maximum size of single file in kilobytes.
        [[nodiscard]] size_t getMaximalFileSizeKiloBytes() const { return maximalFileSize; }

    private:
        size_t numberOfHistoricalFiles;
        size_t maximalFileSize;
    };
}

#endif //ROTATION_FILE_SINK_OPTIONS_H

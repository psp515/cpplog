//
// Created by psp515 on 18.04.2025.
//

#ifndef FILE_SINK_ERRORS_H
#define FILE_SINK_ERRORS_H

#include <string>
#include <stdexcept>

using namespace std;

namespace cpplog::common
{
    /// Options for configuring file sink output, including file and folder names.
    class FileSinkOptions
    {
    public:
        ///
        /// Creates default options for file sink. Initializes both the log file and folder name to "logs".
        ///
        FileSinkOptions()
            : log_file_name("logs.txt"), log_folder_name("logs"), clean(true)
        {
        }

        ///
        /// Creates options for file sink, with properties provided by user.
        ///
        /// @param file_name Name of the log file with extnesion.
        /// @param folder_name Name of the folder where logs will be stored.
        /// @param clean_on_initialize Tells when initializing sink, file for logs should be cleaned.
        explicit FileSinkOptions(const string& file_name, const string& folder_name, const bool clean_on_initialize)
            : log_file_name(file_name), log_folder_name(folder_name), clean(clean_on_initialize)
        {
            if (log_file_name.empty())
            {
                throw invalid_argument("Log file name cannot be empty.");
            }

            if (log_folder_name.empty())
            {
                throw invalid_argument("Log folder name cannot be empty.");
            }
        }

        ///
        /// Gets the configured log file name.
        ///
        /// @return The name of the log file.
        [[nodiscard]] string baseFileName() const { return log_file_name; }

        ///
        /// Gets the configured log folder name.
        ///
        /// @return The name of the log folder.
        [[nodiscard]] string folderName() const { return log_folder_name; }


        ///
        /// Property tells if we should clean all logs on initialize.
        ///
        /// @return If file should be cleaned on initialize.
        [[nodiscard]] bool cleanOnInitialize() const { return clean; }

    private:
        string log_file_name;
        string log_folder_name;
        bool clean;
    };
}

#endif // FILE_SINK_ERRORS_H

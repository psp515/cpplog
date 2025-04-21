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
        FileSinkOptions();

        ///
        /// Creates options for file sink, with properties provided by user.
        ///
        /// @param file_name Name of the log file with extnesion.
        /// @param folder_name Name of the folder where logs will be stored.
        /// @param clean_on_initialize Tells when initializing sink, file for logs should be cleaned.
        explicit FileSinkOptions(const string& file_name, const string& folder_name, const bool clean_on_initialize);

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

        ///
        /// Virtual destructor for proper resource release.
        ///
        virtual ~FileSinkOptions() = default;

    protected:

        ///
        /// Virtual validate function that is called by ctor on creation
        ///
        virtual void validate();

    private:
        string log_file_name;
        string log_folder_name;
        bool clean;
    };
}

#endif // FILE_SINK_ERRORS_H

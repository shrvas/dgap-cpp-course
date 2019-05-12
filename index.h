#include <map>
#include <string>
#include <memory>
using namespace std;

enum file_type
{
    ft_dir,
    ft_reg,
};

struct file_info
{
    string name;
    string path;
    file_type type;
    size_t size;
    size_t mtime;
};

class FileIndexer
{
public:
    FileIndexer(const std::string &rootPath);
    ~FileIndexer();

    /*
     * Build deep file index starting from root dir.
     * Put info about files into map: "Full path" -> file_info.
     * Store file_info as shared_ptr. Do not use pure pointers inside this class.
     * Return number of files found.
     */
    unsigned Build();

    enum SortingType {
        Name,
        Size,
        Time,
		None
    };

    /*
     * Print file list to cout unsorted/sorted.
     * Use table-view to print all info about files.
     */
    void PrintFiles();
    void PrintFilesSorted(SortingType type);

    /*
     * Find file paths by pattern and print them unsorted.
     * Return number of found files.
     */
    unsigned FindFiles(const std::string &pattern);

    /*
     * Move file selected by path.
     * Return status: success or fail.
     */
    bool Movefile(const std::string &path, const std::string &new_path);

    /*
     * Delete file selected by path.
     * Return status: success or fail.
     */
    bool Deletefile(const std::string &path);

private:
    string path;
    map<string, shared_ptr<file_info>> data;
};


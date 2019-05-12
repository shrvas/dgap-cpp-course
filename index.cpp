
#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include <Windows.h>
#include "index.h"
using namespace std;

typedef shared_ptr<file_info> fi_ptr;

vector<file_info*> read_directory(string path)
{
	string s_path = path + "/*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(s_path.c_str(), &fd);
	if (hFind == INVALID_HANDLE_VALUE)
		return vector<file_info*>();

	vector<file_info*> vec;
	do {
		file_info *info = new file_info;
		string name = fd.cFileName;
        if (name == "." || name == "..")
            continue;

        info->path = path + "\\" + name;
        info->name = name;
		info->mtime = fd.ftLastWriteTime.dwLowDateTime;
		info->size = (size_t)fd.nFileSizeLow | (((size_t)fd.nFileSizeHigh) << 32);
		info->type = (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ? ft_dir : ft_reg;
		vec.push_back(info);
	} while (FindNextFile(hFind, &fd));

	FindClose(hFind);
	return vec;
}

FileIndexer::FileIndexer(const string& _path) {
    path = _path;
}
unsigned FileIndexer::Build() {
    queue<fi_ptr> files;
    data.clear();
    auto buff = read_directory(path);
    do{
        if(files.size())
            files.pop();
        for(auto e : buff)
            if(e->type == file_type::ft_dir)
                files.push(fi_ptr(e));
            else
                data.insert(pair<string,fi_ptr>(e->path, fi_ptr(e)));
		if(files.size())
		  buff = read_directory(files.front()->path);
    } while(files.size());
    return data.size();
}
void FileIndexer::PrintFiles() {
	PrintFilesSorted(SortingType::None);
}
void FileIndexer::PrintFilesSorted(SortingType type) {
	vector<fi_ptr> cp;
	for (auto e : data)
		cp.push_back(e.second);
	switch (type)
	{
	case FileIndexer::Name:
		sort(cp.begin(), cp.end(), 
			[](const fi_ptr& a, const fi_ptr& b) {
			
			for (int i = 0; i < min(a->name.size(),b->name.size()); i++)
				if (a->name[i] != b->name[i])
					return a->name[i] < b->name[i];

			if (a->name.size() != b->name.size())
				return a->name.size() < b->name.size();

			return false;

		});
		break;
	case FileIndexer::Size:
		sort(cp.begin(), cp.end(),
			[](const fi_ptr& a, const fi_ptr& b) {
			return a->size < b->size;
		});
		break;
	case FileIndexer::Time:
		sort(cp.begin(), cp.end(),
			[](const fi_ptr& a, const fi_ptr& b) {
			return a->mtime < b->mtime;
		});
		break;
	default:
		break;
	}
	printf("%-40s%-10s%-15s%s\n", "Name", "Size", "Time", "Path");
	for (auto f : cp)
		printf("%-40s%-10d%-15u%s\n", f->name.c_str(), f->size, f->mtime,f->path.substr(0,f->path.size()-f->name.size()).c_str());


}
unsigned FileIndexer::FindFiles(const string& p) {
	unsigned r = 0;
	for(auto f : data)
		if (f.second->path.find(p) != -1) {
			cout << f.second->path << endl;
			r++;
		}
	return r;
}
bool FileIndexer::Movefile(const std::string &path, const std::string &new_path) {
	bool r = MoveFileA(path.c_str(), new_path.c_str());
	Build();
	return r;
}
bool FileIndexer::Deletefile(const std::string &path) {
	bool r = DeleteFileA(path.c_str());
	Build();
	return r;
}

FileIndexer::~FileIndexer(){}

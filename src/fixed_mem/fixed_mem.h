// Author: scandgy  <382333871@qq.com>
#ifndef GPERF_SRC_FIXED_MEM_FIXED_MEM_H_
#define GPERF_SRC_FIXED_MEM_FIXED_MEM_H_

namespace tcmalloc {

static const size_t kDefaultFixedMemSize = (128 * 1024 * 1024)u;

class FixedMemory
{
private:
    // forbid copy construct & assign
    FixedMemory(const FixedMemory& rhs);
    FixedMemory& operator = (const FixedMemory& rhs);

public:
    FixedMemory();

    ~FixedMemory();

    /// init fixed memory
    /// @param name  memory file's name.
    /// @param base_address  the memory address in the calling process address space where mapping begins.
    /// @param size  the min size of memory.
    ///              If memory file's size is less then this parameter, expand the memory.
    ///              If this parameter is zero, set as default 128M
    int Init(const char *name, void *base_address, size_t size = 0u);

    /// expand memory file's size
    /// @param size  the size to be expanded.
    ///              If this parameter is zero, expanded to double.
    int Expand(size_t size = 0u);

    /// clean fixed memory
    /// @param size  the size of memory after clean the memory.
    int Clean(size_t size = 0u);

    /// get fixed memory address
    inline void* GetMemory() const { return m_base_address; }

    /// get fixed memory size
    inline size_t GetCapatity() const { return m_mem_size; }

private:
    int CreateMemoryFile();

    int OpenMemoryFile();

    int MapMemoryFile();

    char    m_mem_file_name[];
    void*   m_base_address;
    size_t  m_mem_size;

#ifdef _MSC_VER
    void*   m_file_handle;
#else
    int     m_file_fd;
#endif
};

} // namespace tcmalloc

#endif // !GPERF_SRC_FIXED_MEM_FIXED_MEM_H_


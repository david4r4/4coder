/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 09.02.2016
 *
 * Shared system functions
 *
 */

// TOP

// TODO(allen): Find a new name/classification for this.

#if !defined(FRED_SYSTEM_SHARED_H)
#define FRED_SYSTEM_SHARED_H

struct File_Data{
    char *data;
    u32 size;
    b32 got_file;
};
global File_Data null_file_data = {0};

#define Sys_File_Can_Be_Made_Sig(name) b32 name(char *filename)
internal Sys_File_Can_Be_Made_Sig(system_file_can_be_made);

#define Sys_Get_Binary_Path_Sig(name) i32 name(String *out)
internal Sys_Get_Binary_Path_Sig(system_get_binary_path);

/////////////////////////////////////

struct Shared_Vars{
    File_Track_System track;
    void *track_table;
    u32 track_table_size;
    u32 track_node_size;
    
    Partition scratch;
};

global Shared_Vars shared_vars;

#endif

// BOTTOM

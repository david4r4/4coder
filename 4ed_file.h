/*
 * Mr. 4th Dimention - Allen Webster
 *
 * 24.01.2018
 *
 * Buffer types
 *
 */

// TOP

#if !defined(FRED_FILE_H)
#define FRED_FILE_H

enum Edit_Pos_Set_Type{
    EditPos_None,
    EditPos_CursorSet,
    EditPos_ScrollSet
};
struct File_Edit_Positions{
    GUI_Scroll_Vars scroll;
    Full_Cursor cursor;
    i32 mark;
    f32 preferred_x;
    i32 scroll_i;
    i32 last_set_type;
    b32 in_view;
};

// TODO(NAME): Replace this with markers over time.
struct Text_Effect{
    i32 start, end;
    u32 color;
    f32 seconds_down, seconds_max;
};

union Buffer_Slot_ID{
    Buffer_ID id;
    i16 part[2];
};

struct Marker_Array{
    Marker_Array *next;
    Marker_Array *prev;
    Buffer_Slot_ID buffer_id;
    u32 count;
    u32 sim_max;
    u32 max;
    Marker_Delete_Callback *callback;
    u32 user_data_size;
    u32 rounded_user_data_size;
};

#define MarkerArrayBase(a) (Marker*)((u8*)(a) + sizeof(Marker_Array) + ((Marker_Array*)(a))->rounded_user_data_size)

struct Editing_File_Markers{
    Marker_Array sentinel;
    u32 array_count;
    u32 marker_count;
};

struct Editing_File_Settings{
    i32 base_map_id;
    i32 display_width;
    i32 minimum_base_display_width;
    i32 wrap_indicator;
    Parse_Context_ID parse_context_id;
    b32 dos_write_mode;
    b32 virtual_white;
    Face_ID font_id;
    b8 unwrapped_lines;
    b8 tokens_exist;
    b8 tokens_without_strings;
    b8 is_initialized;
    b8 unimportant;
    b8 read_only;
    b8 never_kill;
    u8 pad[1];
};

struct Editing_File_State{
    Gap_Buffer buffer;
    
    i32 *wrap_line_index;
    i32 wrap_max;
    
    i32 *character_starts;
    i32 character_start_max;
    
    f32 *line_indents;
    i32 line_indent_max;
    
    i32 wrap_line_count;
    
    i32 *wrap_positions;
    i32 wrap_position_count;
    i32 wrap_position_max;
    
    Undo_Data undo;
    
    Cpp_Token_Array token_array;
    Cpp_Token_Array swap_array;
    u32 lex_job;
    b32 tokens_complete;
    b32 still_lexing;
    
    Text_Effect paste_effect;
    
    Dirty_State dirty;
    u32 ignore_behind_os;
    
    File_Edit_Positions edit_pos_space[16];
    File_Edit_Positions *edit_poss[16];
    i32 edit_poss_count;
};

struct Editing_File_Name{
    char name_[256];
    String name;
};

struct File_Node{
    File_Node *next;
    File_Node *prev;
};

struct Editing_File{
    // NOTE(allen): node must be the first member of Editing_File!
    File_Node node;
    Editing_File_Settings settings;
    b32 is_loading;
    b32 is_dummy;
    Editing_File_State state;
    Editing_File_Markers markers;
    Editing_File_Name base_name;
    Editing_File_Name unique_name;
    Editing_File_Name canon;
    Buffer_Slot_ID id;
};

#endif

// BOTTOM

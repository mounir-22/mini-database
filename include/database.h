#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

/* Constants */
#define PAGE_SIZE 4096
#define MAX_PAGES 100
#define TABLE_MAX_PAGES 100
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

/* Row format */
typedef struct {
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];  // +1 for null terminator
    char email[COLUMN_EMAIL_SIZE + 1];        // +1 for null terminator
} Row;

/* Row size calculations */
#define ID_SIZE size_of_attribute(Row, id)
#define USERNAME_SIZE size_of_attribute(Row, username)
#define EMAIL_SIZE size_of_attribute(Row, email)
#define ID_OFFSET 0
#define USERNAME_OFFSET (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

/* Statement types */
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

typedef struct {
    StatementType type;
    Row row_to_insert; // Only used by insert statement
} Statement;

/* Input buffer */
typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

/* Pager */
typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

/* Table */
typedef struct {
    Pager* pager;
    uint32_t root_page_num;
} Table;

/* Node types */
typedef enum {
    NODE_INTERNAL,
    NODE_LEAF
} NodeType;

/* Cursor */
typedef struct {
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table; // Indicates a position one past the last element
} Cursor;

/* Execution results */
typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY
} ExecuteResult;

/* Meta commands results */
typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

/* Prepare results */
typedef enum {
    PREPARE_SUCCESS,
    PREPARE_NEGATIVE_ID,
    PREPARE_STRING_TOO_LONG,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

/* Function declarations */

/* Input buffer functions */
InputBuffer* new_input_buffer();
void close_input_buffer(InputBuffer* input_buffer);
void print_prompt();
void read_input(InputBuffer* input_buffer);

/* Command processing */
MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);
PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
ExecuteResult execute_statement(Statement* statement, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);

/* Row serialization */
void serialize_row(Row* source, void* destination);
void deserialize_row(void* source, Row* destination);
void print_row(Row* row);

/* Pager functions */
Pager* pager_open(const char* filename);
void* get_page(Pager* pager, uint32_t page_num);
void pager_flush(Pager* pager, uint32_t page_num);

/* Table functions */
Table* db_open(const char* filename);
void db_close(Table* table);

/* Cursor functions */
Cursor* table_start(Table* table);
Cursor* table_find(Table* table, uint32_t key);
Cursor* leaf_node_find(Table* table, uint32_t page_num, uint32_t key);
void* cursor_value(Cursor* cursor);
void cursor_advance(Cursor* cursor);

/* B-tree functions */
uint32_t* leaf_node_num_cells(void* node);
void* leaf_node_cell(void* node, uint32_t cell_num);
uint32_t* leaf_node_key(void* node, uint32_t cell_num);
void* leaf_node_value(void* node, uint32_t cell_num);
void initialize_leaf_node(void* node);
void leaf_node_insert(Cursor* cursor, uint32_t key, Row* value);

/* Node access functions */
NodeType get_node_type(void* node);
void set_node_type(void* node, NodeType type);
bool is_node_root(void* node);
void set_node_root(void* node, bool is_root);

/* Constants for node header layout */
const uint32_t NODE_TYPE_SIZE;
const uint32_t NODE_TYPE_OFFSET;
const uint32_t IS_ROOT_SIZE;
const uint32_t IS_ROOT_OFFSET;
const uint32_t PARENT_POINTER_SIZE;
const uint32_t PARENT_POINTER_OFFSET;
const uint8_t COMMON_NODE_HEADER_SIZE;

/* Constants for leaf node header layout */
const uint32_t LEAF_NODE_NUM_CELLS_SIZE;
const uint32_t LEAF_NODE_NUM_CELLS_OFFSET;
const uint32_t LEAF_NODE_HEADER_SIZE;

/* Constants for leaf node body layout */
const uint32_t LEAF_NODE_KEY_SIZE;
const uint32_t LEAF_NODE_KEY_OFFSET;
const uint32_t LEAF_NODE_VALUE_SIZE;
const uint32_t LEAF_NODE_VALUE_OFFSET;
const uint32_t LEAF_NODE_CELL_SIZE;
const uint32_t LEAF_NODE_SPACE_FOR_CELLS;
const uint32_t LEAF_NODE_MAX_CELLS;

#endif // DATABASE_H
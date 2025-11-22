/* 
 * ADVANCED EXTENSION EXAMPLE: Adding WHERE clauses
 * 
 * This file shows how to extend the Mini Database Engine 
 * to support WHERE id = X queries for efficient lookups.
 * 
 * This is an exercise left for the reader, but here's the approach:
 */

#include "../include/database.h"

/* Extended statement types */
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_SELECT_WHERE  // New statement type
} ExtendedStatementType;

/* Extended statement structure */
typedef struct {
    ExtendedStatementType type;
    Row row_to_insert;      // For INSERT
    uint32_t where_id;      // For WHERE id = X
} ExtendedStatement;

/* 
 * STEP 1: Modify the parser to handle WHERE clauses
 * 
 * Example query: "select where id = 5"
 */
PrepareResult prepare_select_where(InputBuffer* input_buffer, ExtendedStatement* statement) {
    // Parse: "select where id = <number>"
    char* keyword = strtok(input_buffer->buffer, " ");  // "select"
    char* where_clause = strtok(NULL, " ");             // "where"
    char* id_keyword = strtok(NULL, " ");               // "id"
    char* equals = strtok(NULL, " ");                   // "="
    char* id_string = strtok(NULL, " ");                // "<number>"
    
    if (!where_clause || strcmp(where_clause, "where") != 0) {
        return PREPARE_SYNTAX_ERROR;
    }
    
    if (!id_keyword || strcmp(id_keyword, "id") != 0) {
        return PREPARE_SYNTAX_ERROR;
    }
    
    if (!equals || strcmp(equals, "=") != 0) {
        return PREPARE_SYNTAX_ERROR;
    }
    
    if (!id_string) {
        return PREPARE_SYNTAX_ERROR;
    }
    
    int id = atoi(id_string);
    if (id < 0) {
        return PREPARE_NEGATIVE_ID;
    }
    
    statement->type = STATEMENT_SELECT_WHERE;
    statement->where_id = (uint32_t)id;
    
    return PREPARE_SUCCESS;
}

/*
 * STEP 2: Implement efficient WHERE execution using B-tree search
 */
ExecuteResult execute_select_where(ExtendedStatement* statement, Table* table) {
    // Use table_find for O(log n) lookup instead of table_start for O(n) scan
    Cursor* cursor = table_find(table, statement->where_id);
    
    // Check if we found the exact key
    void* page = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = *leaf_node_num_cells(page);
    
    if (cursor->cell_num < num_cells) {
        uint32_t key_at_cursor = *leaf_node_key(page, cursor->cell_num);
        
        if (key_at_cursor == statement->where_id) {
            // Found! Print the row
            Row row;
            deserialize_row(cursor_value(cursor), &row);
            print_row(&row);
        } else {
            // Not found
            printf("No rows found.\n");
        }
    } else {
        printf("No rows found.\n");
    }
    
    free(cursor);
    return EXECUTE_SUCCESS;
}

/*
 * STEP 3: Add comparison operators (>, <, >=, <=)
 * 
 * This would require more complex parsing and range queries on the B-tree.
 * For range queries, you'd need to:
 * 
 * 1. Find the starting position with table_find()
 * 2. Iterate using cursor_advance() until condition is false
 * 3. Handle edge cases for empty ranges
 */

/*
 * STEP 4: Add support for multiple columns in WHERE clauses
 * 
 * This requires secondary indices:
 * 
 * 1. Create separate B-trees for each indexed column
 * 2. Store (column_value, primary_key) pairs in secondary indices
 * 3. Query secondary index first, then primary table
 */

/*
 * PERFORMANCE COMPARISON:
 * 
 * Regular SELECT:     O(n) - scans entire table
 * SELECT WHERE id=X:  O(log n) - direct B-tree lookup
 * 
 * For a table with 1 million rows:
 * - Regular SELECT: 1,000,000 comparisons
 * - WHERE lookup: ~20 comparisons
 * 
 * This is why indices are crucial for database performance!
 */

/*
 * CHALLENGE EXERCISES:
 * 
 * 1. Implement WHERE id > X (range query from X to end)
 * 2. Implement WHERE id BETWEEN X AND Y (range query)
 * 3. Add WHERE username = "string" with secondary index
 * 4. Add compound WHERE clauses: WHERE id > 5 AND username = "alice"
 * 5. Implement ORDER BY for different sort orders
 */
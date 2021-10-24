// sefun: table

/**

tbl = new_table(3);
// new with set columns size
tbl = new_table(3, ({12, 20, 8}));
// or set columns size later
table_set_columns_size(tbl, ({12, 20, 8}));

table_set_header(tbl, 0, "第一列");
table_set_header(tbl, 1, "第二列");
table_set_header(tbl, 2, "第三列");
table_append_row(tbl,
    new_table_cell("1.1", TABLE_ALIGN_LEFT),
    new_table_cell("1.2"),
    new_table_cell("1.3", TABLE_ALIGN_RIGHT));
table_append_row(tbl,
    new_table_cell("2.1", TABLE_ALIGN_LEFT),
    new_table_cell("2.2"),
    new_table_cell("2.3", TABLE_ALIGN_RIGHT));
table_append_row(tbl,
    new_table_cell("3.1", TABLE_ALIGN_LEFT),
    new_table_cell("3.2"),
    new_table_cell("3.3", TABLE_ALIGN_RIGHT));
table_set_footer(tbl, 0, "Foot 1");
table_set_footer(tbl, 1, "Foot 2");
table_set_footer(tbl, 2, "Foot 3");

write(table_render(tbl, TABLE_BORDER_SINGLE));

**/

#include <table.h>

class cell
{
// *INDENT-OFF*
    string value;
    int align;
    int width;
// *INDENT-ON*
}

class table
{
// *INDENT-OFF*
    int col_num;
    int *cols_size;
    class cell *headers;
    mixed *rows;
    class cell *footers;
// *INDENT-ON*
}

varargs class table new_table(int col_num, int *cols_size)
{
// *INDENT-OFF*
    class table tbl;
    tbl = new (class table);
    tbl->col_num = col_num;

    if (!cols_size || sizeof(cols_size) != col_num) {
        tbl->cols_size = allocate(col_num);
    } else {
        tbl->cols_size = cols_size;
    }

    return tbl;
// *INDENT-ON*
}

varargs class cell new_table_cell(string val, int align, int width)
{
// *INDENT-OFF*
    int val_width;
    class cell cl;
    cl = new (class cell);

    if (!val) {
        val = "";
    }

    cl->value = val;

    if (!align) {
        align = TABLE_ALIGN_CENTER;
    }

    cl->align = align;
    val_width = strwidth(val);

    if (val_width % 2 == 1) {
        val_width += 1;
    }

    if (width) {
        if (width % 2 == 1) {
            width += 1;
        }

        if (width > val_width) {
            val_width = width;
        }
    }

    cl->width = val_width;

    return cl;
// *INDENT-ON*
}

// 列宽必须为偶数, 如果不是偶数则自动+1
// 以已设定宽度和待设定的最大值为准
class table table_set_columns_size(class table tbl, int *cols_size)
{
// *INDENT-OFF*
    int i;

    if (sizeof(cols_size) != tbl->col_num) {
        return tbl;
    }

    for (i = 0; i < tbl->col_num; i++) {
        if (cols_size[i] % 2 == 1) {
            cols_size[i] += 1;
        }

        if (cols_size[i] > tbl->cols_size[i]) {
            tbl->cols_size[i] = cols_size[i];
        }
    }

    return tbl;
// *INDENT-ON*
}

varargs class table table_set_header(class table tbl, int col, string val, int align)
{
// *INDENT-OFF*
    class cell cl;

    if (col < 0 || col >= tbl->col_num) {
        return tbl;
    }

    if (!tbl->headers) {
        tbl->headers = allocate(tbl->col_num);
    }

    cl = new_table_cell(val, align);

    if (cl->width > tbl->cols_size[col]) {
        tbl->cols_size[col] = cl->width;
    }

    tbl->headers[col] = cl;

    return tbl;
// *INDENT-ON*
}

varargs class table table_append_row(class table tbl, class cell *cells...)
{
// *INDENT-OFF*
    int i;

    if (sizeof(cells) != tbl->col_num) {
        return tbl;
    }

    for (i = 0; i < tbl->col_num; i++) {
        if (cells[i]->width > tbl->cols_size[i]) {
            tbl->cols_size[i] = cells[i]->width;
        }
    }

    if (!tbl->rows) {
        tbl->rows = ({cells});
    } else {
        tbl->rows += ({cells});
    }

    return tbl;
// *INDENT-ON*
}

varargs class table table_set_footer(class table tbl, int col, string val, int align)
{
// *INDENT-OFF*
    class cell cl;

    if (col < 0 || col >= tbl->col_num) {
        return tbl;
    }

    if (!tbl->footers) {
        tbl->footers = allocate(tbl->col_num);
    }

    cl = new_table_cell(val, align);

    if (cl->width > tbl->cols_size[col]) {
        tbl->cols_size[col] = cl->width;
    }

    tbl->footers[col] = cl;

    return tbl;
// *INDENT-ON*
}

// HLINE, VLINE
// TOP_LEFT, TOP_CENTER, TOP_RIGHT
// MIDDLE_LEFT, MIDDLE_CENTER, MIDDLE_RIGHT
// BOTTOM_LEFT, BOTTOM_CENTER, BOTTOM_RIGHT
// *INDENT-OFF*
mapping borders = ([
    TABLE_BORDER_SIMPLE: ({"--", "| ", ".-", "--", "-.", "|-", "--", "-|", "`-", "--", "-`"}),
    TABLE_BORDER_SINGLE: ({"─", "│", "┌", "┬", "┐", "├", "┼", "┤", "└", "┴", "┘"}),
    TABLE_BORDER_SINGLE_BOLD: ({"━", "┃", "┏", "┳", "┓", "┣", "╋", "┫", "┗", "┻", "┛"}),
    TABLE_BORDER_DOUBLE: ({"═", "║", "╔", "╦", "╗", "╠", "╬", "╣", "╚", "╩", "╝"}),
]);
// *INDENT-ON*

int table_filter_style(int style)
{
    if (!borders[style]) {
        style = TABLE_BORDER_SIMPLE;
    }

    return style;
}

string table_char(int position, int style)
{
    style = table_filter_style(style);

    if (!borders[style][position - 1]) {
        return "";
    }

    return borders[style][position - 1];
}

string table_cell_render(class cell cl, int width)
{
    string fmt_align = width + "s";

    if (width == 0) {
        return "";
    }

    if (cl->align == TABLE_ALIGN_LEFT) {
        fmt_align = "%-" + fmt_align;
    } else if (cl->align == TABLE_ALIGN_RIGHT) {
        fmt_align = "%" + fmt_align;
    } else {
        fmt_align = "%|" + fmt_align;
    }

    return sprintf(fmt_align, cl->value);
}

string table_top_render(class table tbl, int style)
{
    int i;
    string hline, top_center;
    string table_str = "";

    style = table_filter_style(style);

    hline = table_char(TABLE_POSITION_HLINE, style);
    top_center = table_char(TABLE_POSITION_TOP_CENTER, style);
    table_str += table_char(TABLE_POSITION_TOP_LEFT, style);

    for (i = 0; i < tbl->col_num; i++) {
        table_str += repeat_string(hline, tbl->cols_size[i] / 2);

        if (i < tbl->col_num - 1) {
            table_str += top_center;
        }
    }

    table_str += table_char(TABLE_POSITION_TOP_RIGHT, style);

    return table_str;
}

string table_middle_render(class table tbl, int style)
{
    int i;
    string hline, middle_center;
    string table_str = "";

    style = table_filter_style(style);

    hline = table_char(TABLE_POSITION_HLINE, style);
    middle_center = table_char(TABLE_POSITION_MIDDLE_CENTER, style);
    table_str += table_char(TABLE_POSITION_MIDDLE_LEFT, style);

    for (i = 0; i < tbl->col_num; i++) {
        table_str += repeat_string(hline, tbl->cols_size[i] / 2);

        if (i < tbl->col_num - 1) {
            table_str += middle_center;
        }
    }

    table_str += table_char(TABLE_POSITION_MIDDLE_RIGHT, style);

    return table_str;
}

string table_bottom_render(class table tbl, int style)
{
    int i;
    string hline, bottom_center;
    string table_str = "";

    style = table_filter_style(style);

    hline = table_char(TABLE_POSITION_HLINE, style);
    bottom_center = table_char(TABLE_POSITION_BOTTOM_CENTER, style);
    table_str += table_char(TABLE_POSITION_BOTTOM_LEFT, style);

    for (i = 0; i < tbl->col_num; i++) {
        table_str += repeat_string(hline, tbl->cols_size[i] / 2);

        if (i < tbl->col_num - 1) {
            table_str += bottom_center;
        }
    }

    table_str += table_char(TABLE_POSITION_BOTTOM_RIGHT, style);

    return table_str;
}

string table_row_render(class table tbl, class cell *cells, int style)
{
    int i;
    string vline;
    string table_str = "";

    style = table_filter_style(style);

    vline = table_char(TABLE_POSITION_VLINE, style);
    table_str += vline;

    for (i = 0; i < tbl->col_num; i++) {
        table_str += table_cell_render(cells[i], tbl->cols_size[i]);

        if (i == tbl->col_num - 1 && style == TABLE_BORDER_SIMPLE) {
            table_str += " |";
        } else {
            table_str += vline;
        }
    }

    return table_str;
}

string table_render_header(class table tbl, int style)
{
    string table_str = "";

    if (!tbl->headers) {
        return "";
    }

    style = table_filter_style(style);

    table_str += table_top_render(tbl, style);
    table_str += "\n";
    table_str += table_row_render(tbl, tbl->headers, style);
    table_str += "\n";

    if (!tbl->footers && !tbl->rows) {
        table_str += table_bottom_render(tbl, style);
    } else {
        table_str += table_middle_render(tbl, style);
    }

    table_str += "\n";

    return table_str;
}

string table_render_body(class table tbl, int style)
{
    int i;
    string table_str = "";

    if (!tbl->rows) {
        return "";
    }

    style = table_filter_style(style);

    if (!tbl->headers) {
        table_str += table_top_render(tbl, style);
        table_str += "\n";
    }


    for (i = 0; i < sizeof(tbl->rows); i++) {
        table_str += table_row_render(tbl, tbl->rows[i], style);
        table_str += "\n";
    }

    if (!tbl->footers) {
        table_str += table_bottom_render(tbl, style);
        table_str += "\n";
    }

    return table_str;
}

string table_render_footer(class table tbl, int style)
{
    string table_str = "";

    if (!tbl->footers) {
        return "";
    }

    style = table_filter_style(style);

    if (!tbl->headers && !tbl->rows) {
        table_str += table_top_render(tbl, style);
        table_str += "\n";
    }

    if (tbl->rows) {
        table_str += table_middle_render(tbl, style);
        table_str += "\n";
    }

    table_str += table_row_render(tbl, tbl->footers, style);
    table_str += "\n";
    table_str += table_bottom_render(tbl, style);
    table_str += "\n";

    return table_str;
}

string table_render(class table tbl, int style)
{
    string header, body, footer;

    header = table_render_header(tbl, style);
    body = table_render_body(tbl, style);
    footer = table_render_footer(tbl, style);

    return header + body + footer;
}

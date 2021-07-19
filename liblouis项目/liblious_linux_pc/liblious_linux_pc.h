#ifndef LIBLIOUS_LINUX_PC_H
#define LIBLIOUS_LINUX_PC_H

#include "liblious_linux_pc_global.h"

class LIBLIOUS_LINUX_PC_EXPORT Liblious_linux_pc
{
public:
    Liblious_linux_pc();
    void simple_test();


    /**
     * @file
     * @brief Public API of liblouis
     */




    typedef unsigned int widechar;

    typedef unsigned short formtype;

    #ifdef _MSC_VER
    #ifdef _EXPORTING
    #define LIBLOUIS_API __declspec(dllexport)
    #else
    #define LIBLOUIS_API __declspec(dllimport)
    #endif
    #else
    #define LIBLOUIS_API
    #endif

    #ifdef __EMSCRIPTEN__
    #include "emscripten.h"
    #define EXPORT_CALL EMSCRIPTEN_KEEPALIVE
    #elif defined(_WIN32)
    #define EXPORT_CALL __stdcall
    LIBLOUIS_API
    char *EXPORT_CALL
    lou_getProgramPath(void);
    #else
    #define EXPORT_CALL
    #endif

    typedef enum {
        plain_text = 0x0000,
        emph_1 = 0x0001,
        emph_2 = 0x0002,
        emph_3 = 0x0004,
        emph_4 = 0x0008,
        emph_5 = 0x0010,
        emph_6 = 0x0020,
        emph_7 = 0x0040,
        emph_8 = 0x0080,
        emph_9 = 0x0100,
        emph_10 = 0x0200,
        computer_braille = 0x0400,
        no_translate = 0x0800,
        no_contract = 0x1000,
        // SYLLABLE_MARKER_1  0x2000,
        // SYLLABLE_MARKER_1  0x4000
        // CAPSEMPH  0x4000
    } typeforms;

    #define italic emph_1
    #define underline emph_2
    #define bold emph_3

    #define comp_emph_1 emph_1
    #define comp_emph_2 emph_2
    #define comp_emph_3 emph_3

    #define EMPH_NAME_BOLD "bold"
    #define EMPH_NAME_ITALIC "italic"
    #define EMPH_NAME_UNDERLINE "underline"

    typedef enum {
        noContractions = 1,
        compbrlAtCursor = 2,
        dotsIO = 4,
        // for historic reasons 8 and 16 are free
        compbrlLeftCursor = 32,
        ucBrl = 64,
        noUndefined = 128,
        partialTrans = 256
    } translationModes;

    #define noUndefinedDots noUndefined

    LIBLOUIS_API
    const char *EXPORT_CALL
    lou_version(void);

    /**
     * Return the size of widechar
     */
    LIBLOUIS_API
    int EXPORT_CALL
    lou_charSize(void);

    LIBLOUIS_API
    int EXPORT_CALL
    lou_translateString(const char *tableList, const widechar *inbuf, int *inlen,
            widechar *outbuf, int *outlen, formtype *typeform, char *spacing, int mode);

    LIBLOUIS_API
    int EXPORT_CALL
    lou_translate(const char *tableList, const widechar *inbuf, int *inlen, widechar *outbuf,
            int *outlen, formtype *typeform, char *spacing, int *outputPos, int *inputPos,
            int *cursorPos, int mode);

    LIBLOUIS_API
    int EXPORT_CALL
    lou_translatePrehyphenated(const char *tableList, const widechar *inbuf, int *inlen,
            widechar *outbuf, int *outlen, formtype *typeform, char *spacing, int *outputPos,
            int *inputPos, int *cursorPos, char *inputHyphens, char *outputHyphens, int mode);

    LIBLOUIS_API
    int EXPORT_CALL
    lou_hyphenate(
            const char *tableList, const widechar *inbuf, int inlen, char *hyphens, int mode);

    /**
     * Convert a string of dot patterns to a string of chars
     *
     * @param[in]  tableList comma separated list of braille tables
     * @param[in]  inbuf widechar string of dot patterns, either in liblouis format or Unicode
     * braille
     * @param[out] outbuf widechar string corresponding to the dot patterns in `inbuf`
     * @param[in,out] length of both `inbuf` and `outbuf`
     * @param[in] mode (deprecated)
     *
     * @return 1 on success and 0 on failure.
     */
    LIBLOUIS_API
    int EXPORT_CALL
    lou_dotsToChar(
            const char *tableList, widechar *inbuf, widechar *outbuf, int length, int mode);
    LIBLOUIS_API
    int EXPORT_CALL
    lou_charToDots(const char *tableList, const widechar *inbuf, widechar *outbuf, int length,
            int mode);
    LIBLOUIS_API
    int EXPORT_CALL
    lou_backTranslateString(const char *tableList, const widechar *inbuf, int *inlen,
            widechar *outbuf, int *outlen, formtype *typeform, char *spacing, int mode);

    LIBLOUIS_API
    int EXPORT_CALL
    lou_backTranslate(const char *tableList, const widechar *inbuf, int *inlen,
            widechar *outbuf, int *outlen, formtype *typeform, char *spacing, int *outputPos,
            int *inputPos, int *cursorPos, int mode);
    /**
     * Print error messages to a file
     *
     * @deprecated As of 2.6.0, applications using liblouis should
     * implement their own logging system.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_logPrint(const char *format, ...);

    /**
     * Specify the name of the file to be used by lou_logPrint.
     *
     * If it is not used, this file is stderr
     *
     * @deprecated As of 2.6.0, applications using liblouis should
     * implement their own logging system.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_logFile(const char *filename);

    /**
     * Read a character from a file, whether big-endian, little-endian or ASCII8
     *
     * and return it as an integer. EOF at end of file. Mode = 1 on first
     * call, any other value thereafter
     */
    LIBLOUIS_API
    int EXPORT_CALL
    lou_readCharFromFile(const char *fileName, int *mode);

    /**
     * Close the log file so it can be read by other functions.
     *
     * @deprecated As of 2.6.0, applications using liblouis should
     * implement their own logging system.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_logEnd(void);

    /**
     * Load and compile a translation table
     *
     * Check the table for errors. If none are found load the table into
     * memory and return a pointer to it. If errors are found return a
     * null pointer. It is called by lou_translateString() and
     * lou_backTranslateString() and also by functions in liblouisutdml
     * and by the tools.
     */
    LIBLOUIS_API
    const void *EXPORT_CALL
    lou_getTable(const char *tableList);

    /**
     * Check a translation table for errors.
     *
     * If no errors are found it load the table into memory and returns a
     * non-zero value. Else the return value is 0.
     */
    LIBLOUIS_API
    int EXPORT_CALL
    lou_checkTable(const char *tableList);

    /**
     * Register a new table resolver. Overrides the default resolver. */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_registerTableResolver(
            char **(EXPORT_CALL *resolver)(const char *table, const char *base));

    /**
     * Compile a table entry on the fly at run-time
     *
     * This function enables you to compile a table entry on the fly at
     * run-time. The new entry is added to tableList and remains in
     * force until lou_free() is called. If tableList has not
     * previously been loaded it is loaded and compiled.
     *
     * @param inString contains the table entry to be added. It may be
     * anything valid. Error messages will be produced if it is invalid.
     *
     * @return 1 on success and 0 on failure.
     */
    LIBLOUIS_API
    int EXPORT_CALL
    lou_compileString(const char *tableList, const char *inString);

    /**
     * Get the typeform bit for the named emphasis class.
     *
     * If the table defines the specified emphasis class the corresponding
     * typeform is returned. Else the return value is 0.
     */
    LIBLOUIS_API
    formtype EXPORT_CALL
    lou_getTypeformForEmphClass(const char *tableList, const char *emphClass);

    /**
     * Return the emphasis class names declared in tableList as a
     * NULL-terminated array of strings. The array is acquired with malloc()
     * and should be released with free(). The strings must not be released,
     * and are no longer valid after lou_free() has been called.
     */
    LIBLOUIS_API
    char const **EXPORT_CALL
    lou_getEmphClasses(const char *tableList);

    /**
     * Set the path used for searching for tables and liblouisutdml files.
     *
     * Overrides the installation path. */
    LIBLOUIS_API
    char *EXPORT_CALL
    lou_setDataPath(const char *path);

    /**
     * Get the path set in the previous function. */
    LIBLOUIS_API
    char *EXPORT_CALL
    lou_getDataPath(void);

    typedef enum {
        LOU_LOG_ALL = 0,
        LOU_LOG_DEBUG = 10000,
        LOU_LOG_INFO = 20000,
        LOU_LOG_WARN = 30000,
        LOU_LOG_ERROR = 40000,
        LOU_LOG_FATAL = 50000,
        LOU_LOG_OFF = 60000
    } logLevels;

    typedef void(EXPORT_CALL *logcallback)(logLevels level, const char *message);

    /**
     * Register logging callbacks
     * Set to NULL for default callback.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_registerLogCallback(logcallback callback);

    /**
     * Set the level for logging callback to be called at
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_setLogLevel(logLevels level);

    typedef enum { LOU_ROW_BRAILLE = 0X2800 } LOU_UnicodeConstants;

    /* ========================= Sort-of private API ========================= */

    /**
     * Definitions of braille dots
     */
    typedef enum BrailleDots {
        LOU_DOT_1 = 0X01,	/** dot 1 */
        LOU_DOT_2 = 0X02,	/** dot 2 */
        LOU_DOT_3 = 0X04,	/** dot 3 */
        LOU_DOT_4 = 0X08,	/** dot 4 */
        LOU_DOT_5 = 0X10,	/** dot 5 */
        LOU_DOT_6 = 0X20,	/** dot 6 */
        LOU_DOT_7 = 0X40,	/** dot 7 */
        LOU_DOT_8 = 0X80,	/** dot 8 */
        LOU_DOT_9 = 0X100,   /** virtual dot 9 */
        LOU_DOT_10 = 0X200,  /** virtual dot A */
        LOU_DOT_11 = 0X400,  /** virtual dot B */
        LOU_DOT_12 = 0X800,  /** virtual dot C */
        LOU_DOT_13 = 0X1000, /** virtual dot D */
        LOU_DOT_14 = 0X2000, /** virtual dot E */
        LOU_DOT_15 = 0X4000, /** virtual dot F */
        LOU_DOTS = 0X8000	/** if this bit is true, the widechar represents a dot pattern */
    } BrailleDots;

    /**
     * A sentinel, used in liblouisutdml
     */
    #define LOU_ENDSEGMENT 0xffff

    /* =========================  BETA API ========================= */

    // Use the following two function with care, API is subject to change!

    /**
     * Parse, analyze and index tables.
     *
     * This function must be called prior to lou_findTable() and
     * lou_listTables(). Table names must be provided as a NULL-terminated
     * array of strings. Each table should resolve to exactly one file. An
     * error message is given when a table contains invalid or duplicate
     * metadata fields.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_indexTables(const char **tables);

    /**
     * Find the best match for a query.
     *
     * Returns the name of the table, or NULL when no match can be
     * found. If lou_indexTables() has not been previously called, the
     * table search path specified with LOUIS_TABLEPATH will be indexed
     * first. An error message is given when the query is invalid. Freeing
     * the memory of the returned string is the responsibility of the
     * caller.
     */
    LIBLOUIS_API
    char *EXPORT_CALL
    lou_findTable(const char *query);

    /**
     * Find all matches for a query, best match first.
     *
     * Returns the names of the matched table as a NULL-terminated array
     * of string. If lou_indexTables() has not been previously called, the
     * table search path specified with LOUIS_TABLEPATH will be indexed
     * first. An error message is given when the query is invalid. Freeing
     * the memory of the returned array and strings is the responsibility
     * of the caller.
     */
    LIBLOUIS_API
    char **EXPORT_CALL
    lou_findTables(const char *query);

    /**
     * Read metadata from a file.
     *
     * Returns the value of the metadata field specified by `key' in
     * `table', or NULL when the field does not exist. Freeing the memory
     * of the returned string is the responsibility of the caller.
     */
    LIBLOUIS_API
    char *EXPORT_CALL
    lou_getTableInfo(const char *table, const char *key);

    /**
     * List available tables.
     *
     * Returns the names of available tables as a NULL-terminated array of
     * strings. Only tables that are discoverable, i.e. the have active
     * metadata, are listed. If lou_indexTables() has not been previously
     * called, the table search path specified with LOUIS_TABLEPATH will
     * be indexed first. Freeing the memory of the returned array and
     * strings is the responsibility of the caller.
     */
    LIBLOUIS_API
    char **EXPORT_CALL
    lou_listTables(void);

    /* ====================== END OF BETA API ====================== */

    /**
     * Free all memory allocated by liblouis.
     *
     * This function should be called at the end of the application to
     * free all memory allocated by liblouis.
     */
    LIBLOUIS_API
    void EXPORT_CALL
    lou_free(void);



};

#endif // LIBLIOUS_LINUX_PC_H

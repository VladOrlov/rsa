class MathException {
    const char *cause;
public:
    const char *getCause() { return cause; }

    MathException(const char *inp) : cause(inp) {}
};


class RsaException {
    const char *cause;
public:
    const char *getCause() { return cause; }

    RsaException(const char *inp) : cause(inp) {}
};


class ArgumentException {
};


class FileIOException {
    const char *filename;
public:
    const char *getFilename() { return filename; }

    FileIOException(const char *inp) : filename(inp) {}
};

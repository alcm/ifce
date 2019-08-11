#include <iostream>
#include <fstream>
#include <memory>

enum class DocumentType { PDF, DOC, LATEX, MARKDOWN };

class Document {
   public:
    virtual void ExportTo(const std::fstream &file) = 0;
};

class Pdf : public Document {
   public:
    void ExportTo(const std::fstream &file) override
    {
        std::cout << "Export to pdf" << std::endl;
    }
};

class Doc : public Document {
   public:
    void ExportTo(const std::fstream &file) override
    {
        std::cout << "Export to doc" << std::endl;
    }
};

class Latex : public Document {
   public:
    void ExportTo(const std::fstream &file) override
    {
        std::cout << "Export to latex" << std::endl;
    }
};

class Markdown : public Document {
   public:
    void ExportTo(const std::fstream &file) override
    {
        std::cout << "Export to markdown" << std::endl;
    }
};

class DocumentFactory {
   public:
    static std::shared_ptr<Document> Create(const DocumentType type)
    {
        switch (type) {
        case DocumentType::PDF:
            return std::make_shared<Pdf>();

        case DocumentType::DOC:
            return std::make_shared<Doc>();

        case DocumentType::LATEX:
            return std::make_shared<Latex>();

        case DocumentType::MARKDOWN:
            return std::make_shared<Markdown>();

        default:
            std::cout << "Format not supported" << std::endl;
            return nullptr;
        }
    }
};

int main()
{
    std::fstream file("/etc/passwd");

    auto doc = DocumentFactory::Create(DocumentType::LATEX);
    doc->ExportTo(file);
}

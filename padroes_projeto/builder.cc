#include <iostream>
#include <string>

struct Notebook {
    std::string model_;
    std::string motherboard_;
    std::string cpu_;
    std::string memory_;
    std::string disk_;
};

class NotebokBuilder {
   public:
    virtual void BuildMotherboard() = 0;
    virtual void BuildCpu() = 0;
    virtual void BuildMemory() = 0;
    virtual void BuildDisk() = 0;
    virtual void BuildModel() = 0;

    Notebook &notebook() const {
        return note_;
    }

   protected:
    Notebook note_;
};

class DellBuilder : public NotebookBuilder {
   public:
    void BuildMotherboard() override
    {
        note_.motherboard.assign();        
    }
    
    void BuildCpu() override
    {
        note_.cpu.assign();
    }

    void BuildMemory() override
    {
        note_.memory.assign();        
    }

    void BuildDisk() override
    {
        note_.disk.assign();        
    }

    void BuildModel() override
    {
        note_.model.assign();        
    }
};

class LenovoBuilder : public NotebookBuilder {
   public:
    void BuildMotherboard() override
    {
        note_.motherboard.assign();        
    }
    
    void BuildCpu() override
    {
        note_.cpu.assign();
    }

    void BuildMemory() override
    {
        note_.memory.assign();        
    }

    void BuildDisk() override
    {
        note_.disk.assign();        
    }

    void BuildModel() override
    {
        note_.model.assign();        
    }
};

int main()
{
    NotebookBuilder *builder = new LenovoBuilder();
}

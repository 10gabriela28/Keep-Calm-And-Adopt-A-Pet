
#pragma once
#include "repup.h"

class UndoAction {
protected:
    Repository* repo;
public:
    UndoAction(Repository* r) : repo(r) {}
    virtual ~UndoAction() = default;
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
};

class UndoAdd : public UndoAction {
private:
    Dog addedDog;
public:
    UndoAdd(Repository* r, const Dog& d) : UndoAction(r), addedDog(d) {}
    void executeUndo() override { repo->removeDog(addedDog); }
    void executeRedo() override { repo->addDog(addedDog); }
};

class UndoRemove : public UndoAction {
private:
    Dog removedDog;
public:
    UndoRemove(Repository* r, const Dog& d) : UndoAction(r), removedDog(d) {}
    void executeUndo() override { repo->addDog(removedDog); }
    void executeRedo() override { repo->removeDog(removedDog); }
};

class UndoUpdate : public UndoAction {
private:
    Dog oldDog;
    Dog newDog;
    int index;
public:
    UndoUpdate(Repository* r, const Dog& oldD, const Dog& newD, int idx) 
        : UndoAction(r), oldDog(oldD), newDog(newD), index(idx) {}
    void executeUndo() override {
        repo->getDogs().updateDog(index, oldDog);
        repo->saveToFile();
    }
    void executeRedo() override {
        repo->getDogs().updateDog(index, newDog);
        repo->saveToFile();
    }
};
/******************************************************************************
**
** Copyright (C) 2009-2011 Kyle Lutz <kyle.r.lutz@gmail.com>
** All rights reserved.
**
** This file is a part of the chemkit project. For more information
** see <http://www.chemkit.org>.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in the
**     documentation and/or other materials provided with the distribution.
**   * Neither the name of the chemkit project nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
******************************************************************************/

#include "moleculeeditortest.h"

#include <chemkit/atom.h>
#include <chemkit/bond.h>
#include <chemkit/moleculeeditor.h>

void MoleculeEditorTest::basic()
{
    chemkit::MoleculeEditor editor;
    QVERIFY(editor.molecule() == 0);

    chemkit::Molecule molecule;
    chemkit::MoleculeEditor editor2(&molecule);
    QVERIFY(editor2.molecule() == &molecule);
}

void MoleculeEditorTest::setMolecule()
{
    chemkit::MoleculeEditor editor;
    QVERIFY(editor.molecule() == 0);

    chemkit::Molecule molecule;
    editor.setMolecule(&molecule);
    QVERIFY(editor.molecule() == &molecule);

    chemkit::Molecule molecule2;
    editor.setMolecule(&molecule2);
    QVERIFY(editor.molecule() == &molecule2);

    editor.setMolecule(0);
    QVERIFY(editor.molecule() == 0);
}

void MoleculeEditorTest::addAtom()
{
    chemkit::Molecule molecule;
    chemkit::MoleculeEditor editor(&molecule);
    QVERIFY(editor.molecule() == &molecule);

    editor.addAtom(6);
    editor.addAtom(6);
    editor.addAtom(6);
    QCOMPARE(molecule.formula(), std::string("C3"));

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("C2"));

    editor.redo();
    QCOMPARE(molecule.formula(), std::string("C3"));

    editor.removeAtom(molecule.atom(0));
    QCOMPARE(molecule.formula(), std::string("C2"));

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("C3"));

    editor.redo();
    QCOMPARE(molecule.formula(), std::string("C2"));

    editor.removeAtom(molecule.atom(1));
    editor.removeAtom(molecule.atom(0));
    QCOMPARE(molecule.formula(), std::string());

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("C"));

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("C2"));
}

void MoleculeEditorTest::removeAtom()
{
    chemkit::Molecule molecule;
    chemkit::Atom *C1 = molecule.addAtom(chemkit::Atom::Carbon);
    chemkit::Atom *O2 = molecule.addAtom(chemkit::Atom::Oxygen);
    QCOMPARE(molecule.formula(), std::string("CO"));

    chemkit::MoleculeEditor editor(&molecule);
    editor.removeAtom(C1);
    QCOMPARE(molecule.formula(), std::string("O"));

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("CO"));

    editor.redo();
    QCOMPARE(molecule.formula(), std::string("O"));
}

void MoleculeEditorTest::setAtomElement()
{
    chemkit::Molecule molecule;
    chemkit::Atom *atom = molecule.addAtom(6);
    chemkit::MoleculeEditor editor(&molecule);
    editor.setAtomElement(atom, 1);
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(1));

    editor.undo();
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(6));

    editor.redo();
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(1));

    editor.setAtomElement(atom, 2);
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(2));

    editor.setAtomElement(atom, 3);
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(3));

    editor.undo();
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(2));

    editor.undo();
    QCOMPARE(atom->atomicNumber(), chemkit::Atom::AtomicNumberType(1));
}

void MoleculeEditorTest::setAtomPosition()
{
    chemkit::Molecule molecule;
    chemkit::Atom *atom = molecule.addAtom(chemkit::Atom::Carbon);
    QVERIFY(atom->position() == chemkit::Point3(0, 0, 0));

    chemkit::MoleculeEditor editor(&molecule);
    editor.setAtomPosition(atom, chemkit::Point3(1, 2, 3));
    QVERIFY(atom->position() == chemkit::Point3(1, 2, 3));

    editor.undo();
    QVERIFY(atom->position() == chemkit::Point3(0, 0, 0));

    editor.redo();
    QVERIFY(atom->position() == chemkit::Point3(1, 2, 3));
}

void MoleculeEditorTest::addBond()
{
    chemkit::Molecule molecule;
    chemkit::MoleculeEditor editor(&molecule);
    QVERIFY(editor.molecule() == &molecule);

    chemkit::Atom *C1 = editor.addAtom(6);
    chemkit::Atom *C2 = editor.addAtom(6);
    chemkit::Atom *C3 = editor.addAtom(6);
    QCOMPARE(molecule.formula(), std::string("C3"));

    chemkit::Bond *C1_C2 = editor.addBond(C1, C2);
    QCOMPARE(molecule.bondCount(), size_t(1));

    chemkit::Bond *C2_C3 = editor.addBond(C2, C3, chemkit::Bond::Double);
    QCOMPARE(C2_C3->order(), chemkit::Bond::BondOrderType(2));
    QCOMPARE(molecule.bondCount(), size_t(2));

    editor.removeBond(C1_C2);
    QCOMPARE(molecule.bondCount(), size_t(1));

    editor.undo();
    QCOMPARE(molecule.bondCount(), size_t(2));

    editor.redo();
    QCOMPARE(molecule.bondCount(), size_t(1));

    editor.removeBond(C2_C3);
    QCOMPARE(molecule.bondCount(), size_t(0));

    editor.undo();
    QCOMPARE(molecule.bondCount(), size_t(1));
    QCOMPARE(molecule.bonds()[0]->order(), chemkit::Bond::BondOrderType(2));
}

void MoleculeEditorTest::removeBond()
{
    chemkit::Molecule molecule;
    chemkit::MoleculeEditor editor(&molecule);
    chemkit::Atom *C1 = molecule.addAtom("C");
    chemkit::Atom *C2 = molecule.addAtom("C");
    chemkit::Bond *bond = molecule.addBond(C1, C2);
    QCOMPARE(molecule.bondCount(), size_t(1));

    editor.removeBond(bond);
    QCOMPARE(molecule.bondCount(), size_t(0));
    QCOMPARE(C1->isBondedTo(C2), false);

    editor.undo();
    QCOMPARE(molecule.bondCount(), size_t(1));
    QCOMPARE(C1->isBondedTo(C2), true);

    editor.redo();
    QCOMPARE(molecule.bondCount(), size_t(0));
    QCOMPARE(C1->isBondedTo(C2), false);
}

void MoleculeEditorTest::setBondOrder()
{
    chemkit::Molecule molecule;
    chemkit::MoleculeEditor editor(&molecule);
    chemkit::Atom *C1 = molecule.addAtom("C");
    chemkit::Atom *C2 = molecule.addAtom("C");
    chemkit::Bond *bond = molecule.addBond(C1, C2);
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(1));

    editor.setBondOrder(bond, 2);
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(2));

    editor.undo();
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(1));

    editor.redo();
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(2));

    editor.setBondOrder(bond, 3);
    editor.setBondOrder(bond, 2);
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(2));

    editor.undo();
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(3));

    editor.undo();
    QCOMPARE(bond->order(), chemkit::Bond::BondOrderType(2));
}

void MoleculeEditorTest::cut()
{
    chemkit::Molecule molecule;
    chemkit::Atom *C1 = molecule.addAtom("C");
    chemkit::Atom *C2 = molecule.addAtom("C");
    chemkit::Atom *O3 = molecule.addAtom("O");
    molecule.addBond(C1, C2);
    molecule.addBond(C2, O3, 2);
    QCOMPARE(molecule.formula(), std::string("C2O"));
    QCOMPARE(molecule.bondCount(), size_t(2));

    chemkit::MoleculeEditor editor(&molecule);
    editor.cut(std::vector<chemkit::Atom *>(molecule.atoms().begin(),
                                            molecule.atoms().end()));
    QCOMPARE(editor.copyBuffer().size(), size_t(3));
    QCOMPARE(molecule.formula(), std::string(""));
    QCOMPARE(molecule.bondCount(), size_t(0));

    editor.paste();
    QCOMPARE(molecule.formula(), std::string("C2O"));
    QCOMPARE(molecule.bondCount(), size_t(2));

    editor.undo();
    QCOMPARE(molecule.formula(), std::string(""));
    QCOMPARE(molecule.bondCount(), size_t(0));

    editor.redo();
    QCOMPARE(molecule.formula(), std::string("C2O"));
    QCOMPARE(molecule.bondCount(), size_t(2));
}

void MoleculeEditorTest::copy()
{
    chemkit::Molecule molecule;
    chemkit::Atom *C1 = molecule.addAtom("C");
    chemkit::Atom *C2 = molecule.addAtom("C");
    chemkit::Atom *O3 = molecule.addAtom("O");
    molecule.addBond(C1, C2);
    molecule.addBond(C2, O3, 2);
    QCOMPARE(molecule.formula(), std::string("C2O"));
    QCOMPARE(molecule.bondCount(), size_t(2));

    chemkit::MoleculeEditor editor(&molecule);
    editor.copy(std::vector<chemkit::Atom *>(molecule.atoms().begin(),
                                             molecule.atoms().end()));
    QCOMPARE(editor.copyBuffer().size(), size_t(3));

    editor.paste();
    QCOMPARE(molecule.formula(), std::string("C4O2"));
    QCOMPARE(molecule.bondCount(), size_t(4));
    foreach(chemkit::Atom *atom, molecule.atoms()){
        if(atom->is(chemkit::Atom::Oxygen)){
            QCOMPARE(atom->isBondedTo(chemkit::Atom::Carbon, chemkit::Bond::Double), true);
        }
        else if(atom->is(chemkit::Atom::Carbon)){
            QCOMPARE(atom->isBondedTo(chemkit::Atom::Carbon, chemkit::Bond::Single), true);
        }
    }

    editor.undo();
    QCOMPARE(molecule.formula(), std::string("C2O"));
    QCOMPARE(molecule.bondCount(), size_t(2));

    editor.redo();
    QCOMPARE(molecule.formula(), std::string("C4O2"));
    QCOMPARE(molecule.bondCount(), size_t(4));

    std::vector<chemkit::Atom *> oxygens;
    foreach(chemkit::Atom *atom, molecule.atoms()){
        if(atom->is(chemkit::Atom::Oxygen)){
            oxygens.push_back(atom);
        }
    }
    editor.copy(oxygens);
    QCOMPARE(editor.copyBuffer().size(), size_t(2));

    std::vector<chemkit::Atom *> newAtoms = editor.paste();
    QCOMPARE(newAtoms.size(), size_t(2));
    foreach(chemkit::Atom *atom, newAtoms){
        QCOMPARE(atom->is(chemkit::Atom::Oxygen), true);
    }
    QCOMPARE(molecule.formula(), std::string("C4O4"));
    QCOMPARE(molecule.bondCount(), size_t(4));
}

void MoleculeEditorTest::clearCopyBuffer()
{
    chemkit::MoleculeEditor editor;
    QCOMPARE(editor.copyBuffer().size(), size_t(0));
    editor.clearCopyBuffer();
    QCOMPARE(editor.copyBuffer().size(), size_t(0));

    chemkit::Molecule molecule;
    molecule.addAtom("H");
    molecule.addAtom("H");
    editor.setMolecule(&molecule);
    editor.copy(std::vector<chemkit::Atom *>(molecule.atoms().begin(),
                                             molecule.atoms().end()));
    QCOMPARE(editor.copyBuffer().size(), size_t(2));
    editor.clearCopyBuffer();
    QCOMPARE(editor.copyBuffer().size(), size_t(0));
}

QTEST_APPLESS_MAIN(MoleculeEditorTest)

/*
 * Souffle - A Datalog Compiler
 * Copyright (c) 2018, The Souffle Developers. All rights reserved
 * Licensed under the Universal Permissive License v 1.0 as shown at:
 * - https://opensource.org/licenses/UPL
 * - <souffle root>/licenses/SOUFFLE-UPL.txt
 */

/************************************************************************
 *
 * @file Loop.h
 *
 * Defines the interface for RAM transformation passes.
 *
 ***********************************************************************/

#pragma once

#include "ram/TranslationUnit.h"
#include "ram/transform/Meta.h"
#include <memory>
#include <string>
#include <utility>

namespace souffle {

/**
 * @Class RamLoopTransformer
 * @Brief Composite loop transformer
 *
 * A transformation is invoked iteratively until no further change
 * is made.
 */
class RamLoopTransformer : public RamMetaTransformer {
public:
    RamLoopTransformer(Own<RamTransformer> tLoop) : loop(std::move(tLoop)) {}
    std::string getName() const override {
        return "RamLoopTransformer";
    }
    bool transform(RamTranslationUnit& tU) override {
        int ctr = 0;
        while (loop->apply(tU)) {
            ctr++;
        }
        return ctr > 0;
    }

protected:
    /** transformer of the loop */
    Own<RamTransformer> loop;
};

}  // end of namespace souffle

/** @file featurelist.h
 *  @brief FeatureList class
 */
/* Copyright (C) 2016 Ayush Tomar
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#ifndef FEATURE_LIST_H
#define FEATURE_LIST_H

#include <xapian.h>
#include <xapian/intrusive_ptr.h>
#include <xapian/types.h>
#include <xapian/visibility.h>

#include "feature.h"
#include "featurevector.h"

#include <map>
#include <string>
#include <vector>

namespace Xapian {

/// Class defining list of features to be used for constructing FeatureVector
class XAPIAN_VISIBILITY_DEFAULT FeatureList {

    /// Vector containing Feature pointer objects. Each will be used to return feature value.
    std::vector<Feature *> feature;

  public:

    /** Default constructor. Initializes vector<Feature*> with ALL Feature
     * sub-classes available in "feature.h".
     *
     * Note: Weight of a document assigned by Xapian Weighting scheme is added
     *       as a feature by default.
     */
    FeatureList();

    /** Constructor initialsing with custom Feature objects.
     *
     * @param f Vector of Feature pointer objects.
     * e.g. vector<Feature*> features;
     *      features.push_back(new TfFeature());
     *      features.push_back(new IdfFeature());
     *
     * Note: Weight of a document assigned by Xapian Weighting scheme is added
     *       as a feature by default. Hence, even in case of empty initialisation,
     *       Weight will be used as a deafult feature.
     */
    FeatureList(const std::vector<Feature*> & f);

    /// Copy constructor
    FeatureList(const FeatureList & o);

    /// Assignment
    FeatureList & operator=(const FeatureList & o);

    /// Destructor
    ~FeatureList();

    /** Returns a vector of FeatureVectors for each document in the MSet for a given query.
     *
     *  @ param  mset        MSet for which the vector<FeatureVector> is to be returned
     *  @ param  letor_query Query for which the vector<FeatureVector> is to be returned
     *  @ param  letor_db    Corresponding Database
     */
    std::vector<Xapian::FeatureVector> create_feature_vectors(const Xapian::MSet & mset,
							     const Xapian::Query & letor_query,
							     const Xapian::Database & letor_db);

  private:

    /// Perform query-level normalisation of FeatureVectors.
    void normalise(std::vector<FeatureVector> & fvec);

};

}

#endif // FEATURE_LIST_H

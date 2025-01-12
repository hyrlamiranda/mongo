/**
 *    Copyright (C) 2015 MongoDB Inc.
 *
 *    This program is free software: you can redistribute it and/or  modify
 *    it under the terms of the GNU Affero General Public License, version 3,
 *    as published by the Free Software Foundation.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *    As a special exception, the copyright holders give permission to link the
 *    code of portions of this program with the OpenSSL library under certain
 *    conditions as described in each individual source file and distribute
 *    linked combinations including the program with the OpenSSL library. You
 *    must comply with the GNU Affero General Public License in all respects for
 *    all of the code used other than as permitted herein. If you modify file(s)
 *    with this exception, you may extend this exception to your version of the
 *    file(s), but you are not obligated to do so. If you do not wish to do so,
 *    delete this exception statement from your version. If you delete this
 *    exception statement from all source files in the program, then also delete
 *    it in the license file.
 */

#pragma once

#include "mongo/util/background.h"

namespace mongo {

/**
 * Background job which regularly performs cleanup tasks on the ClusterCursorManager owned by the
 * Grid singleton.
 *
 * Cleanup tasks include:
 * - Killing cursors that have been inactive for some time.
 * - Reaping cursors that have been killed.
 */
class ClusterCursorCleanupJob final : public BackgroundJob {
public:
    /**
     * Period of time after which mortal cursors are killed for inactivity. Configurable with
     * server parameter "cursorTimeoutMillis".
     *
     * TODO: Move declaration to cpp file once CursorCache class is deleted. See SERVER-20194 for
     * more details.
     */
    static long long cursorTimeoutMillis;

    std::string name() const final;
    void run() final;
};

extern ClusterCursorCleanupJob clusterCursorCleanupJob;

}  // namespace mongo

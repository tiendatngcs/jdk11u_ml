/*
 * Copyright (c) 2018, Red Hat, Inc. All rights reserved.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef SHARE_VM_GC_SHENANDOAH_HEURISTICS_SHENANDOAHQTABLEHEURISTICS_HPP
#define SHARE_VM_GC_SHENANDOAH_HEURISTICS_SHENANDOAHQTABLEHEURISTICS_HPP

#include "gc/shenandoah/heuristics/shenandoahHeuristics.hpp"
#include "gc/shenandoah/shenandoahPhaseTimings.hpp"
#include "utilities/numberSeq.hpp"
#include <cstdlib>

class ShenandoahQTableHeuristics : public ShenandoahHeuristics {
public:
  ShenandoahQTableHeuristics();

  virtual ~ShenandoahQTableHeuristics();

  virtual void choose_collection_set_from_regiondata(ShenandoahCollectionSet* cset,
                                                     RegionData* data, size_t size,
                                                     size_t actual_free);

  void record_cycle_start();

  virtual bool should_start_gc();

  virtual const char* name()     { return "QTable"; }
  virtual bool is_diagnostic()   { return false; }
  virtual bool is_experimental() { return false; }

private:
  double _qtable[128][2];
  bool _is_first_call;
  bool _last_action;
  double _last_time_since_last;
  size_t _last_available;

  //  from the second call of should_start_gc()
  // Calculate the reward 
  double get_reward(size_t available, size_t capacity);
  //  update the qtable with the current state and the previous saved current state
  void update_qtable();

  // Record the current state and take action with the curernt state (explorative or exploitative)
  bool take_action(bool in_learning);

};

#endif // SHARE_VM_GC_SHENANDOAH_HEURISTICS_SHENANDOAHQTABLEHEURISTICS_HPP

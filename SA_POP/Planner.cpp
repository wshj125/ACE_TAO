// -*- C++ -*-
// $Id$

//=============================================================================
/**
 * @file  Planner.cpp
 *
 * This file contains the Planner abstract base class implementation for planners,
 * which direct planning and mediate communication between other planning
 * objects.
 *
 * @author  John S. Kinnebrew <john.s.kinnebrew@vanderbilt.edu>
 */
//=============================================================================

#include <string>
#include <set>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include "SA_POP_Types.h"
#include "Planner.h"
#include "PlanStrategy.h"
#include "SchedStrategy.h"
#include "WorkingPlan.h"
#include "TaskMap.h"
#include "OutAdapter.h"
#include "PlanCommands.h"

using namespace SA_POP;

// Constructor.
Planner::Planner (void)
: cond_prob_thresh_ (SA_POP::Default::COND_PROB_THRESH),
has_objs_ (false),
sanet_ (0),
plan_strat_ (0),
sched_strat_ (0),
working_plan_ (0),
task_map_ (0),
cur_cmd_ (0)
{
  this->out_adapters_.clear ();
  this->eu_changes_.clear ();

  // Clear plan.
  this->plan_.causal_links.clear ();
  this->plan_.connections.clear ();
  this->plan_.sched_links.clear ();
  this->plan_.task_insts.clear ();
  this->plan_.threat_links.clear ();

  this->not_backtracking.decision_pt = -1;
  this->not_backtracking.seq_num = -1;
  this->not_backtracking.step = -1;

  this->backtrack_cmd = this->not_backtracking;
};


/// Destructor.
Planner::~Planner (void)
{
  delete this->sanet_;
  delete this->plan_strat_;
  delete this->sched_strat_;
  delete this->working_plan_;
  delete this->task_map_;

  //****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****
  // Delete output adapters??????
}



// Add planning objects.
void Planner::set_objects (SANet::Network *sanet, PlanStrategy *plan_strat,
SchedStrategy *sched_strat, WorkingPlan *working_plan, TaskMap *task_map)
{
  this->has_objs_ = true;

  if (sanet != 0)
    this->sanet_ = sanet;
  else if (this->sanet_ == 0)
    this->has_objs_ = false;

  if (plan_strat != 0)
    this->plan_strat_ = plan_strat;
  else if (this->plan_strat_ == 0)
    this->has_objs_ = false;

  if (sched_strat != 0)
    this->sched_strat_ = sched_strat;
  else if (this->sched_strat_ == 0)
    this->has_objs_ = false;

  if (working_plan != 0)
    this->working_plan_ = working_plan;
  else if (this->working_plan_ == 0)
    this->has_objs_ = false;

  if (task_map != 0)
    this->task_map_ = task_map;
  else if (this->task_map_ == 0)
    this->has_objs_ = false;
};

// Add output adapter.
void Planner::add_out_adapter (OutAdapter *out)
{
  this->out_adapters_.insert (out);
};

// Run planning.
bool Planner::plan (size_t sa_max_steps, SA_POP::Goal goal)
{
  // Add goal to working plan and task network.
  this->working_plan_->set_goal (goal);
  this->sanet_->update_goals (goal.goal_conds);

  // Reset network and run spreading activation.
  this->sanet_->reset_sa ();
  this->sanet_->update (sa_max_steps);

  // Set planning strategy goals and satisfy open conditions.
  this->plan_strat_->set_goals (goal.goal_conds);

  if (this->plan_strat_->satisfy_open_conds ()) {
    this->plan_ = this->working_plan_->get_plan ();

    this->notify_plan_changed ();
    return true;
  }

  return false;
};

// Replan with new goal.
bool Planner::replan (size_t sa_max_steps, SA_POP::Goal goal)
{
  //****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****
  // Full replanning not implemented, so just restart planning.
  //****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****

  // Clear plan.
  this->plan_.clear ();

  // Reset the working plan
  this->working_plan_->reset_plan ();

  // Add goal to working plan and task network.
  this->working_plan_->set_goal (goal);
  this->sanet_->update_goals (goal.goal_conds);

  // Reset network and run spreading activation.
  this->sanet_->reset_sa ();
  this->sanet_->update (sa_max_steps);

  // Set planning strategy goals and satisfy open conditions.
  this->plan_strat_->set_goals (goal.goal_conds);
  if (this->plan_strat_->satisfy_open_conds ()) {
    this->plan_ = this->working_plan_->get_plan ();
    this->notify_plan_changed ();
    return true;
  }

  return false;
};

// Replan with existing goal.
bool Planner::replan (size_t sa_max_steps)
{
  //****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****
  // Full replanning not implemented, so just restart planning.
  //****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****TEMP****
  // Clear plan.
  this->plan_.clear ();

  // Reset the working plan
  this->working_plan_->reset_plan ();

  // Reset network and run spreading activation.
  this->sanet_->reset_sa ();
  this->sanet_->update (sa_max_steps);

  // Set planning strategy goals and satisfy open conditions.
  this->plan_strat_->set_goals (this->sanet_->get_goals ());
  if (this->plan_strat_->satisfy_open_conds ()) {
    this->plan_ = this->working_plan_->get_plan ();
    this->notify_plan_changed ();
    return true;
  }

  return false;
};

// Get current plan.
const Plan& Planner::get_plan (void)
{
  this->plan_ = this->working_plan_->get_plan ();
  return this->plan_;
};

// Get last set of expected utility changes.
const TaskEUMap& Planner::get_eu_changes (void)
{
  return this->eu_changes_;
};

// Print a text representation of the task network.
void Planner::print_sanet (std::basic_ostream<char, std::char_traits<char> >& strm,
                           bool verbose)
{
  this->sanet_->print (strm, verbose);
};

// Print the graphviz representation of the task network.
void Planner::print_sanet_graphviz (std::basic_ostream<char, std::char_traits<char> >& strm, std::map<std::string, std::string>& graphmap)
{
  this->sanet_->print_graphviz(strm, graphmap);
};

// Recursively plan (satisfy all open conditions & schedule constraints).
bool Planner::recurse_plan (void)
{
  return this->plan_strat_->satisfy_open_conds ();
};

// Recursively schedule (satisfy schedule constraints and continue
// recursive planning).
bool Planner::recurse_sched (TaskInstID task_inst)
{
  return this->sched_strat_->satisfy_sched (task_inst);
};

// Satisfy scheduling constraints in fully instantiated plan (no
// recursive call backs).
bool Planner::full_sched ()
{
  return this->sched_strat_->satisfy_full_sched ();
};

// Execute a command (adding it as the current command).
void Planner::execute_command (PlanCommand *command)
{
  command->set_prev (this->cur_cmd_);
  this->cur_cmd_ = command;
  this->cur_cmd_->execute_next ();
};

// Undo and remove command.
void Planner::undo_command (CommandID id)
{
  if (this->cur_cmd_->get_id () != id)
    this->undo_through (id);

  if (this->cur_cmd_ == 0) {
    char char_buf[35];
    sprintf(char_buf, "%d.%d.%d", id.step, id.decision_pt, id.seq_num); 
    std::string msg = "Planner::undo_command (): no command history ";
    msg += "(command id ";
    msg += char_buf;
    msg += ")";
    throw msg;
  }

  PlanCommand* tmp = this->cur_cmd_;
  this->cur_cmd_->undo ();
  this->cur_cmd_ = this->cur_cmd_->get_prev ();

  delete tmp;
};

// Add a command to be executed later with execute_next().
void Planner::add_command (PlanCommand *command)
{
  command->set_prev (this->cur_cmd_);
  this->cur_cmd_ = command;
};

// On current command, undo last execution (if any) & execute next option.
bool Planner::try_next (CommandID id)
{
	if(this->backtrack_cmd != this->not_backtracking){
		if(id != this->backtrack_cmd){
			return false;
		}else{
			this->backtrack_cmd = this->not_backtracking;
		}
	}

  if (this->cur_cmd_->get_id () != id) {
    char char_buf[35];
    sprintf(char_buf, "%d.%d.%d", id.step, id.decision_pt, id.seq_num); 
    std::string msg = "Planner::try_next (): command id ";
    msg += char_buf;
    msg += " is not current command in history.";
    throw msg;
  }

  return this->cur_cmd_->execute_next ();
};

// Undo and remove all commands back to specified point.
void Planner::undo_through (CommandID id)
{
  if (this->cur_cmd_ == 0) {
    char char_buf[35];
    sprintf(char_buf, "%d.%d.%d", id.step, id.decision_pt, id.seq_num); 
    std::string msg = "Planner::undo_through (): command id ";
    msg += char_buf;
    msg += " could not be found.";
    throw msg;
  }

  if (this->cur_cmd_->get_id () == id)
    return;

  PlanCommand *temp = this->cur_cmd_;
  temp->undo ();
  this->cur_cmd_ = temp->get_prev ();

  delete temp;


  this->undo_through (id);
};
/// Get the current command id.
CommandID Planner::cur_command_id()
{
  return this->cur_cmd_->get_id();
}

// Update a condition's current value (probability of being true).
void Planner::update_cond_val (CondID cond_id, double true_prob)
{
  this->sanet_->update_cond_val (cond_id, true_prob);
};

// Get a condition's current value (probability of being true).
double Planner::get_cond_val (CondID cond_id)
{
  return this->sanet_->get_cond_val (cond_id);
};

// Get all goals.
const GoalMap& Planner::get_goals (void)
{
  return this->sanet_->get_goals ();
};

// Get a task's name.
std::string Planner::get_task_name (TaskID task_id)
{
	if(task_id == INIT_TASK_ID){
		return "init task";
	}

  return this->sanet_->get_task_name (task_id);
};

// Get a condition's name.
std::string Planner::get_cond_name (CondID cond_id)
{
  return this->sanet_->get_cond_name (cond_id);
};

// Get a condition's type/kind.
CondKind Planner::get_cond_type (CondID cond_id)
{
  return this->sanet_->get_cond_type (cond_id);
};

// Get a task's future expected utility (EU) from spreading activation.
// (NOTE: Future EU is based on whatever spreading
// activation has already been executed).
Utility Planner::get_task_sa_eu (TaskID task_id)
{
  return this->sanet_->get_task_sa_eu (task_id);
};

// Get all preconditions of a task.
CondSet Planner::get_preconds (TaskID task_id)
{
  return this->sanet_->get_preconds (task_id);
};

// Get currently unsatisfied preconditions of a task.
CondSet Planner::get_unsat_preconds (TaskID task_id)
{
  CondSet temp = this->get_preconds (task_id);

  //Note:  removed because when threats exist, it is wrong.  Uses initial condition
  ///instead
  /*
  // Remove satisfied preconditions.
  for (CondSet::iterator iter = temp.begin ();
    iter != temp.end (); )
  {
    CondSet::iterator prev_iter = iter;
    iter++;

    // Get current probability of needed value for condition.
    Probability cur_prob = this->get_cond_val ((*prev_iter).id);
    if (!(*prev_iter).value)
      cur_prob = 1 - cur_prob;

    // Remove condition if probability is greater than threshold.
    if (cur_prob > this->cond_prob_thresh_)
      temp.erase (prev_iter);
  }
  
  */
  

  return temp;
}


// Get all effects of a task.
CondSet Planner::get_effects (TaskID task_id)
{
  return this->sanet_->get_effects (task_id);
};

// Get the probability of a task's effect.
SANet::LinkWeight Planner::get_effect_prob(SANet::TaskID id, SANet::CondID cond_ID)
{
  return this->sanet_->get_effect_prob(id, cond_ID);
}

// Get all tasks that satisfy a condition.
TaskSet Planner::get_satisfying_tasks (Condition cond)
{
  return this->sanet_->get_satisfying_tasks (cond);
};

// Get ports for a causal link.
LinkPorts Planner::get_clink_ports (TaskID task1_id, CondID cond_id,
                                    TaskID task2_id)
{
  return this->sanet_->get_clink_ports(task1_id, cond_id, task2_id);
};

// Get task id of a task instance.
TaskID Planner::get_task_from_inst (TaskInstID inst_id)
{
  return this->working_plan_->get_task_from_inst (inst_id);
};

void Planner::generate_all_threats(void)
{
   this->working_plan_->generate_all_threats();
}

// Get all current causal link threats.
CLThreatSet Planner::get_all_threats (void)
{
  return this->working_plan_->get_all_threats ();
};

// Get all implementations of a task.
TaskImplSet Planner::get_all_impls (TaskID task_id)
{
  return this->task_map_->get_all_impls (task_id);
};

// Get task implementation.
TaskImpl *Planner::get_impl (TaskImplID impl_id)
{
  return this->task_map_->get_impl (impl_id);
};

// Get utilization info of a task implementation for a resource.
ResourceValue Planner::get_resource_usage (TaskImplID impl_id,
ResourceID resource_id)
{
  return this->task_map_->get_resource_usage (impl_id, resource_id);
};

// Get all resources used by a task implementation.
ResourceMap Planner::get_all_resources (TaskImplID impl_id)
{

	if(impl_id == INIT_TASK_IMPL_ID){
		return SA_POP::ResourceMap();
	}

  return this->task_map_->get_all_resources (impl_id);
};

void Planner::notify_plan_changed (void)
{
  for (std::set<OutAdapter *>::iterator iter = this->out_adapters_.begin ();
    iter != this->out_adapters_.end (); iter++)
  {
    (*iter)->notify_plan (this);
  }
};

Utility Planner::calc_plan_eu(Plan plan)
{
  // Probability of goal conditions should be completely updated
  // by spreading activation for <= 2 times the number of tasks
  // in the plan (because even a serial plan will be of no longer
  // than the number of tasks and times 2 to account for
  // update of condition nodes between tasks).
//*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****
//  size_t sa_max_steps = 2 * plan.task_insts.size ();
  // Set to times 3 to be extra certain that sufficient SA is done.
  size_t sa_max_steps = 3 * plan.task_insts.size ();
//*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****TEMP*****

  // Clone current SANet.
  SANet::Network sanet (*(this->sanet_));

  // Reset network.
  sanet.reset_sa ();

  // Deactivate all nodes, before activating relevant ones.
  sanet.set_nodes_state (false);

  SA_POP::Goal goal = plan.goal;

//  std::ostringstream goal_str;
//  goal_str << "Activated goal conditions: ";

  // Activate goal conditions.
  for (SA_POP::GoalMap::iterator goal_iter = goal.goal_conds.begin (); goal_iter != goal.goal_conds.end (); goal_iter++) {
//    goal_str << this->get_cond_name (goal_iter->first) << " ";
    sanet.set_cond_state (goal_iter->first, true);
  }

//  SA_POP_DEBUG_STR(SA_POP_DEBUG_VERBOSE, goal_str.str ());

  // Activate tasks in plan and their preconditions.
  for (PlanInstSet::iterator inst_iter = plan.task_insts.begin (); inst_iter != plan.task_insts.end (); inst_iter++) {
    if ((*inst_iter).inst_id == INIT_TASK_INST_ID) {
      std::cerr << "SA_POP::Planner::calc_plan_eu(Plan plan):  Initial state task instance found in plan." << std::endl;
      throw "SA_POP::Planner::calc_plan_eu(Plan plan):  Initial state task instance found in plan.";
    }

//    std::ostringstream temp_str;
//    temp_str << "Activated task [instance] and ( preconditions ): ";
//    temp_str << this->get_task_name ((*inst_iter).task_id);
//    temp_str << " [" << (*inst_iter).name << "] and ( ";

    // Activate task.
    sanet.set_task_state ((*inst_iter).task_id, true);

    // Activate preconditions.
    SA_POP::CondSet preconds = this->get_preconds ((*inst_iter).task_id);
    for (SA_POP::CondSet::iterator cond_iter = preconds.begin (); cond_iter != preconds.end (); cond_iter++) {
//      temp_str << this->get_cond_name ((*cond_iter).id) << " ";
      sanet.set_cond_state ((*cond_iter).id, true);
    }

//    temp_str << ")";
//    SA_POP_DEBUG_STR(SA_POP_DEBUG_VERBOSE, temp_str.str ());
  }

  // Run spreading activation.
	sanet.update(sa_max_steps);

//  std::ostringstream eu_str;
//  eu_str << "Goals (probability, EU):  ";

  // Calculate sum of expected utility for goals.
  SA_POP::Utility eu_total = 0.0;
  for (SA_POP::GoalMap::iterator goal_iter = goal.goal_conds.begin (); goal_iter != goal.goal_conds.end (); goal_iter++) {
//    eu_str << this->get_cond_name (goal_iter->first) << " (";
    SA_POP::Probability prob = 0.0;
    SA_POP::Utility util = 0.0;
    SA_POP::Utility eu = 0.0;

    // Set probability and utility of goal condition achieving desired value
    // of true (if positive utility) or false (if negative utility).
    if (goal_iter->second > 0) {
      prob = sanet.get_cond_future_val (goal_iter->first, true);
      util = goal_iter->second;
    }
    else {
      prob = sanet.get_cond_future_val (goal_iter->first, false);
      util = -1 * goal_iter->second;
    }

    // Expected utility of the goal condition is its probability times utility.
    eu = prob * util;

    eu_total += eu;

//    eu_str << prob << ", " << eu << ")  " ;
  }

//  SA_POP_DEBUG_STR(SA_POP_DEBUG_VERBOSE, eu_str.str ());

  return eu_total;
};

/// Get the Task instances in a particular set of the specified task instance
const TaskInstSet* Planner::get_prec_insts (TaskInstID task_inst, PrecedenceRelation prec_rel)
{
	return this->working_plan_->get_prec_set(task_inst,prec_rel);
}

/// Get the Start Window of the Task instance
TimeWindow Planner::get_start_window (TaskInstID task_inst)
{
	return this->working_plan_->get_start_window(task_inst);
}

/// Get the End Window of the Task instance
TimeWindow Planner::get_end_window (TaskInstID task_inst)
{
	return this->working_plan_->get_end_window(task_inst);
}

/// Get task implementation id of a task instance.
TaskImplID Planner::get_task_impl_from_inst (TaskInstID inst_id)
{
	return this->working_plan_->get_task_impl_from_inst(inst_id);
}

/// Get the capacity of a resource.
ResourceValue Planner::get_capacity (ResourceID res_id)
{
  return this->task_map_->get_capacity(res_id);
}

//Get the duration of a task instance
TimeValue Planner::get_duration(TaskInstID task_inst)
{
  return this->working_plan_->get_duration(task_inst);
}
/// Get the Causal and Scheduling orderings from this task instance
TaskInstSet Planner::after_orderings (TaskInstID inst_id)
{
  return this->working_plan_->after_orderings(inst_id);
}

/// Get the Causal and Scheduling orderings to this task instance
TaskInstSet Planner::before_orderings (TaskInstID inst_id)
{
  return this->working_plan_->before_orderings(inst_id);
}

/// Get all the task instances
TaskInstSet Planner::get_all_insts()
{
	return this->working_plan_->get_all_insts();
}

/// Check if the instance id already exists and is being reused.
bool Planner::inst_exists (TaskInstID task_inst)
{
  return this->working_plan_->inst_exists(task_inst);
}

/// Get task implementation for a task instance.
TaskImplID Planner::get_impl_id (TaskInstID task_inst)
{
  return this->working_plan_->get_impl_id(task_inst);

}


//Allows the planner to update an effect link
void Planner::update_effect (SANet::TaskID tsk, SANet::CondID cnd, SANet::LinkWeight weight)
{
  this->sanet_->update_effect_link(tsk, cnd, weight);

}

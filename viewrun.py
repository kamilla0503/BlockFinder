#!/usr/bin/python -u

import argparse
import re
import math

def scan_tasks(taskfile):
   num_tasks = 0
   tasks = []
   with open(taskfile, "r") as task:
      for line in task:
         num_tasks+= 1
   return(num_tasks)

task_run_re= re.compile('^\\[Task(\d+)\\] +(\d+)M +(\d+) sec')
task_finished_re = re.compile('^\\[Task(\d+)\\] finished task (\d+) after (\d+) iterations')

def scan_log(logfiles_list, n_tasks):
   log_lines_in_all_files = 0
   list_task_time = [None for t in range(n_tasks)]
   list_task_iter = [None for t in range(n_tasks)]
   list_task_finished = [False for t in range(n_tasks)]

   for logfile in logfiles_list:
      print("Start {} scan".format(logfile))
      with open(logfile, "r") as log:
        log_lines = 0
        for line in log:
           log_lines += 1
           log_lines_in_all_files += 1
           task_run_match = task_run_re.match(line)
           if task_run_match:
              task_num =  int(task_run_match.group(1))
              task_iter = int(task_run_match.group(2))*1000000
              task_sec  = int(task_run_match.group(3))
              list_task_iter[task_num] = task_iter
              list_task_time[task_num] = task_sec
              continue
           task_finished_match = task_finished_re.match(line)
           if task_finished_match:
              task_num =  int(task_finished_match.group(1))
              task_iter = int(task_finished_match.group(3))
              list_task_iter[task_num] = task_iter
              list_task_finished[task_num] = True
              
        print("Scan of log file {} finished, {:,} lines scanned".format(logfile, log_lines))
        
   print("Scan of all {} log files finished, {:,} lines scanned".\
      format(len(logfiles_list), log_lines_in_all_files))

   total_iter = 0
   total_finished = 0
   total_none = 0
   total_running = 0

   out_line_len = 100
   out_n_lines = math.floor(n_tasks/out_line_len) + 1
   out_line = "{:>5} ".format(1)
   out_line_num = 0
   
   for task_num in range(n_tasks):
      
      if not ( task_num % out_line_len ) and not task_num == 0:
         out_line += " {:>5}".format(task_num)
         print(out_line)
         out_line_num += 1
         out_line = ""
         out_line += "{:>5} ".format(task_num+1)


      if list_task_iter[task_num]:
         total_iter += list_task_iter[task_num]
         if not list_task_finished[task_num]:
            total_running += 1
            out_line += "*"
      else:
         total_none += 1
         out_line += "."
      if list_task_finished[task_num]:
         total_finished += 1
         out_line += "F"
   
   rest_size = ( n_tasks ) % out_line_len
   out_line_fill= out_line + (" " * (out_line_len - rest_size ) )+ " {:>5}".format(n_tasks)
   print(out_line_fill)
      
    
   print("Task status: {} finished, {} running and {} waiting ".format(total_finished, total_running, total_none))
   print("Total {:,} iterations in all tasks".format(total_iter))



   return( (list_task_time, list_task_iter, list_task_finished) )
         
      

if __name__ == '__main__':
   parser = argparse.ArgumentParser()
   parser.add_argument("log", help='Log file to scan', type=str, nargs='+')
   parser.add_argument("--tasks", "-t", help='Tasks file', type=str, default="tasksend.txt")
   args = parser.parse_args()
   n_tasks = scan_tasks(args.tasks)
   print("Number of tasks = {}".format(n_tasks))
   stat = scan_log(args.log, n_tasks)

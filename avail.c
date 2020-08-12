#ifdef CODE
#include "stdio.h"
#include "omp.h"
#include "omp-tools.h"

int main()
{
  #pragma omp parallel num_threads(2)
  {
    #pragma omp master
    {
      int result = omp_control_tool(omp_control_tool_start, 0, NULL);
      printf("0: control_tool()=%d\n", result);
    }
  }
  
  return 0;
}

#endif /* CODE */

#ifdef TOOL

#include <omp-tools.h>
#include "stdio.h"

#ifdef SECOND_TOOL

ompt_start_tool_result_t* ompt_start_tool(
  unsigned int omp_version,
  const char *runtime_version)
{
  printf("0: Do not initialize tool\n");
  return NULL;
}
#elif defined(THIRD_TOOL)

static void
on_ompt_callback_thread_begin(
  ompt_thread_t thread_type,
  ompt_data_t *thread_data)
{
  printf("0: ompt_event_thread_begin\n");
}

int ompt_initialize(
  ompt_function_lookup_t lookup,
  ompt_data_t *tool_data)
{
  ompt_set_callback_t ompt_set_callback = (ompt_set_callback_t) lookup("ompt_set_callback");
  ompt_set_callback(ompt_callback_thread_begin, (ompt_callback_t)on_ompt_callback_thread_begin);
  printf("0: Tool initialized\n");
  return 1;
}

void ompt_finalize(ompt_data_t *tool_data)
{
  printf("0: Tool finalized\n");
}

ompt_start_tool_result_t* ompt_start_tool(
  unsigned int omp_version,
  const char *runtime_version)
{
  printf("0: Do initialize tool\n");
  static ompt_start_tool_result_t ompt_start_tool_result = {&ompt_initialize,&ompt_finalize, 0};
  return &ompt_start_tool_result;
}
#endif

#endif /* TOOL */

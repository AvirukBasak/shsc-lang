# Memory Usage Tests

## Address Sanitizer v/s Memory Usage

High memory usage is noticed during the debug build.
Where the debug build may use `522 MiB`, the release build may use less than `5 MiB` under similar conditions.

After disabling address sanitizer in debug flags, the debug build is noticed to have reduced memory usage similar to the release build.
This indicates that the address sanitizer is the cause of the high memory usage.

## Memory Usage Tests

This README provides a comparison of different configuration options in a code execution scenario of the **DEBUG BUILD ONLY**, including the impact on memory usage and execution time. The configurations under consideration are "push/pop scope," "create i," and the presence of the variable assignment `var x = "Hi"`. We will also analyze the stability of resident memory usage (Stable RES) and the time taken for process memory to stabilize (Stable ETA) in seconds.

## Configuration Options

### push/pop scope
- "yes" indicates that `rt::VarTable::push_scope` and `rt::VarTable::pop_scope` are enabled, resulting in frequent memory allocation and deallocation.
- "no" means that these operations are not enabled, resulting in fewer memory allocation and deallocation operations.

### create i
- "yes" indicates that the for loop implementation is creating a variable within the loop  using `rt::VarTable::create` to maintain an enumeration in the specified loop range.
- "no" means that the loop does not create the variable.

### var x = "Hi"
- "yes" indicates that the following code is executed:
  ```python
  proc main start
      for i from 0 to 10000000000 do
          var x = "Hi"
      end
  end
  ```
- "no" indicates that the following code is executed instead:
  ```python
  proc main start
      for i from 0 to 10000000000 do
      end
  end
  ```

## Usage Observation

The table below summarizes the memory usage (in MiB) and the time taken for process memory to stabilize (Stable ETA) in seconds for different configurations:

| push/pop scope | create i | var x = "Hi" | Stable RES (MiB)  | Stable ETA (s) |
|----------------|----------|--------------|-------------------|----------------|
| no             | no       | no           | 6.2               | 0              |
| no             | no       | yes          | 6.4               | 0              |
| no             | yes      | no           | 7.4               | 0              |
| no             | yes      | yes          | 15.4              | 0              |
| yes            | no       | no           | 470.0             | 5              |
| yes            | no       | yes          | 503.9             | 5              |
| yes            | yes      | yes          | 522.4             | 7              |

## Interpretation

1. Enabling the "push/pop scope" option significantly increases memory usage and execution time compared to when it's disabled. This is because frequent memory allocation and deallocation operations result in higher memory fragmentation and overhead.

2. The "create i" option has a relatively modest impact on memory usage and execution time, but it does lead to a slightly higher memory usage when enabled.

3. The presence of the variable assignment `var x = "Hi"` has a noticeable effect on memory usage. When enabled, it increases memory usage, especially in conjunction with the "push/pop scope" option.

4. The combination of "push/pop scope" and "create i" significantly increases memory usage and execution time. It's important to consider whether the benefits of using these options outweigh the associated resource costs.

5. The "Stable RES" values represent the memory usage at a stable state, indicating how much memory is required after the code execution has stabilized.

6. The "Stable ETA" values denote the time it takes for process memory to stabilize in seconds.

## Conclusion

The choice of configuration options can have a significant impact on memory usage and execution time in your code. It's important to carefully consider the trade-offs between memory usage and code readability, especially when dealing with large datasets or resource-constrained environments. The optimal configuration may vary depending on your specific use case and requirements.

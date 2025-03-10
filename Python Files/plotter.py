# x and y given as array_like objects
import plotly.express as px
import polars as pl
import numpy as np 


# For Sorting
# df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Sorting")
# print(df)

# fig = px.line(df, x="Elements", y=["GoInsertion", "CInsertion"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Insertion Time Comparison")
# fig.show()

# fig = px.line(df, x="Elements", y=["GoBubble", "CBubble"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Bubble Time Comparison")
# fig.show()

# fig = px.line(df, x="Elements", y=["GoMerge", "CMerge"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Merge Time Comparison")
# fig.show()

# fig = px.line(df, x="Elements", y=["GoQuick", "CQuick"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Quick Time Comparison")
# fig.show()


# # For Fib
# df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Fib")
# print(df)

# fig = px.line(df, x="Input", y=["GoFibIter", "CFibIter"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Fibonacci Iterative Time Comparison")
# fig.show()

# fig = px.line(df, x="Input", y=["GoFibRecurs", "CFibRecurs"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Fibonacci Recursive Time Comparison")
# fig.show()

# # For Matrix Mult
# df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="MatrixMult")
# print(df)

# fig = px.line(df, x="Element Iterations", y=["GoMatrixMult", "CMatrixMult"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Matrix Multiplication Time Comparison")
# fig.show()

# # For Prime Number Calculations
# df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Prime")
# print(df)

# fig = px.line(df, x="Input", y=["GoIsPrime", "CIsPrime"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Prime Number Calculations Time Comparison")
# fig.show()

###################################################################################################################################################

# MemoryUsage C
# df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Benchmarking Data CS263 Final.xlsx", sheet_name="MemoryUsage C")

# print(df)

# fig = px.line(df, x="Time (s)", y="Total Allocated Memory (MB)", 
#               labels={"Time (s)": "Time (s)", "Total Allocated Memory (MB)": "Total Allocated Memory (MB)", "variable": "Method"},
#               title="Memory Usage in C")
# fig.show()

# df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Benchmarking Data CS263 Final.xlsx", sheet_name="MemoryUsage Go")
# print(df)

# fig = px.line(df, x="Time (s)", y="Total Allocated Memory (MB)", 
#               labels={"Time (s)": "Time (s)", "Total Allocated Memory (MB)": "Total Allocated Memory (MB)", "variable": "Method"},
#               title="Memory Usage in Go")
# fig.show()

# df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Benchmarking Data CS263 Final.xlsx", sheet_name="MemoryUsage Go")
# print(df)

# fig = px.line(df, x="Time (s)", y="GC Cycles", 
#               labels={"Time (s)": "Time (s)", "GC Cycles" : "GC Cycles", "variable": "Method"},
#               title="Memory Usage in Go")
# fig.show()

# df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Benchmarking Data CS263 Final.xlsx", sheet_name="Copy Pasting")

# print(df)

# df_melted = df.unpivot(
#     index=["Tasks"],  
#     on=["Time to Build C Files", "Time to Build Go Files"], 
#     variable_name="File Type",  
#     value_name="Build Time"  
# )
# print(df_melted)


# fig = px.bar(df_melted, x="Tasks", y="Build Time", color="File Type", 
#              barmode="group", title="Build Times for C and Go Files")

# fig.show()

df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Data\Benchmarking Data CS263 Final.xlsx", sheet_name="Concurrency Runtime")
print(df)

fig = px.line(df, x="Thread Count", y=["C", "Go"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Multi-Threading Concurrency Runtime")
fig.show()

df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Data\Benchmarking Data CS263 Final.xlsx", sheet_name="Concurrency Runtime")
print(df)
df = df.rename({"C_1": "C Shared Resources", "Go_1": "Go Shared Resources"})
fig = px.line(df, x="Thread Count_1", y=["C Shared Resources", "Go Shared Resources"], 
              labels={"value": "Time (s)", "Thread Count_1": "Thread Count", "variable": "Method"},
              title="Shared Resources Concurrency Runtime")
fig.show()

df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Data\Benchmarking Data CS263 Final.xlsx", sheet_name="Concurrency Runtime")
print(df)

fig = px.line(df, x="Thread Count_2", y=["Go Shared", "Go MultiThread"], 
              labels={"value": "Time (s)", "Thread Count_2": "Thread Count", "variable": "Method"},
              title="Go Compared")
fig.show()
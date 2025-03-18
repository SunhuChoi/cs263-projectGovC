# x and y given as array_like objects
import plotly.express as px
import polars as pl
import numpy as np 


# For Sorting
# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3.xlsx", sheet_name="Sorting with O3")
# print(df)

# fig = px.line(df, x="Elements", y=["GoInsertion", "CInsertion"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Insertion Time Comparison with GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoBubble", "CBubble"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Bubble Time Comparison with GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoMerge", "CMerge"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Merge Time Comparison with GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoQuick", "CQuick"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Quick Time Comparison with GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )


# fig.show()

# #################################################################################################################################################

# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3.xlsx", sheet_name="Sorting without O3")
# print(df)

# fig = px.line(df, x="Elements", y=["GoInsertion", "CInsertion"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Insertion Time Comparison without GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoBubble", "CBubble"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Bubble Time Comparison without GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoMerge", "CMerge"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Merge Time Comparison without GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# fig = px.line(df, x="Elements", y=["GoQuick", "CQuick"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Quick Time Comparison without GCC O3")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )


# fig.show()

# #################################################################################################################################################

# # For Fib
# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3.xlsx", sheet_name="Fib with O3")
# print(df)

# fig = px.line(df, x="Input", y=["GoFibIter", "CFibIter", "CFibIter -O3"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Fibonacci Iterative Time Comparison")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )
# fig.show()

# fig = px.line(df, x="Input", y=["GoFibRecurs", "CFibRecurs", "CFibRecurs -O3"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Fibonacci Recursive Time Comparison")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

# # For Matrix Mult
# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3.xlsx", sheet_name="MatrixMult with O3")
# print(df)

# fig = px.line(df, x="Element Iterations", y=["GoMatrixMult", "CMatrixMult -O3","CMatrixMult "], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Matrix Multiplication Time Comparison")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )
# fig.show()

# # For Prime Number Calculations
# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3.xlsx", sheet_name="Prime with O3")
# print(df)

# fig = px.line(df, x="Input", y=["GoIsPrime", "CIsPrime", "CIsPrime -O3"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Prime Number Calculations Time Comparison")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )
# fig.show()

##################################################################################################################################################

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

########################################################################################################################################################

# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Bar Chart 2.xlsx", sheet_name="bar graph")

# print(df)

# df = df.rename({"Multhithreading Program": "Multithreading Program"})


# df_melted = df.unpivot(
#     index=["Tasks"],  
#     on=["Multithreading Program", "Mergesort"], 
#     variable_name="File Type",  
#     value_name="Build Time"  
# )
# print(df_melted)


# fig = px.bar(df_melted, x="Tasks", y="Build Time", color="File Type", 
#              barmode="group", title="Build Times for C and Go Files")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     },
#     bargap=0.58
# )
# fig.update_traces(width=0.2)
# fig.show()

###############################################################################################################################################################################################################################

# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3 With Conc.xlsx", sheet_name="Concurrency Runtime with O3")
# print(df)

# fig = px.line(df, x="Thread Count", y=["C", "Go", "C -O3"], 
#               labels={"value": "Time (s)", "variable": "Method"},
#               title="Multi-Threading Concurrency Runtime")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )

# fig.show()

##############################################################################################################################################################################

# df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Benchmarking Data CS263 with O3 With Conc.xlsx", sheet_name="Concurrency Runtime with O3")
# print(df)
# df = df.rename({"C_1": "C Shared Resources", "Go_1": "Go Shared Resources", "C -O3_1": "C -O3 Sharaed Resources"})
# fig = px.line(df, x="Thread Count_1", y=["C Shared Resources", "Go Shared Resources", "C -O3 Sharaed Resources"], 
#               labels={"value": "Time (s)", "Thread Count_1": "Thread Count", "variable": "Method"},
#               title="Shared Resources Concurrency Runtime")

# fig.update_layout(
#     title={
#         "x": 0.5,  # Centers the title
#         "xanchor": "center",  # Ensures proper centering
#         "yanchor": "top",  # Positions it at the top
#         "font": {"weight": "bold"},  # Bold font
#     }
# )
# fig.show()

#####################################################################################################################################################################

# df = pl.read_excel(r"C:\Users\svnhu\CS263\cs263-projectGovC\Data\Benchmarking Data CS263 Final.xlsx", sheet_name="Concurrency Runtime")
# print(df)

# fig = px.line(df, x="Thread Count_2", y=["Go Shared", "Go MultiThread"], 
#               labels={"value": "Time (s)", "Thread Count_2": "Thread Count", "variable": "Method"},
#               title="Go Compared")
# fig.show()

######################################################################################################################################################################

df = pl.read_excel(r"C:\Users\svnhu\CS263 Final\cs263-projectGovC\Data\Machines Results.xlsx", sheet_name="Bubble Sort Machines")
print(df)

fig = px.line(df, x="Elements", y=["CBubble WindowsOS", "CBubble macOS", "CBubble LinuxOS"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Bubble Sort Across Different Machines for C")

fig.update_layout(
    title={
        "x": 0.5,  # Centers the title
        "xanchor": "center",  # Ensures proper centering
        "yanchor": "top",  # Positions it at the top
        "font": {"weight": "bold"},  # Bold font
    }
)
fig.show()

fig = px.line(df, x="Elements", y=["GoBubble WindowsOS", "GoBubble macOS", "GoBubble LinuxOS" ], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Bubble Sort Across Different Machines for Go")

fig.update_layout(
    title={
        "x": 0.5,  # Centers the title
        "xanchor": "center",  # Ensures proper centering
        "yanchor": "top",  # Positions it at the top
        "font": {"weight": "bold"},  # Bold font
    }
)
fig.show()
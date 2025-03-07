# x and y given as array_like objects
import plotly.express as px
import polars as pl
import numpy as np 


# For Sorting
df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Sorting")
print(df)

fig = px.line(df, x="Elements", y=["GoInsertion", "CInsertion"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Insertion Time Comparison")
fig.show()

fig = px.line(df, x="Elements", y=["GoBubble", "CBubble"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Bubble Time Comparison")
fig.show()

fig = px.line(df, x="Elements", y=["GoMerge", "CMerge"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Merge Time Comparison")
fig.show()

fig = px.line(df, x="Elements", y=["GoQuick", "CQuick"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Quick Time Comparison")
fig.show()


# For Fib
df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Fib")
print(df)

fig = px.line(df, x="Input", y=["GoFibIter", "CFibIter"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Fibonacci Iterative Time Comparison")
fig.show()

fig = px.line(df, x="Input", y=["GoFibRecurs", "CFibRecurs"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Fibonacci Recursive Time Comparison")
fig.show()

# For Matrix Mult
df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="MatrixMult")
print(df)

fig = px.line(df, x="Element Iterations", y=["GoMatrixMult", "CMatrixMult"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Matrix Multiplication Time Comparison")
fig.show()

# For Prime Number Calculations
df = pl.read_excel(r"c:\Users\svnhu\Downloads\Benchmarking Data CS263.xlsx", sheet_name="Prime")
print(df)

fig = px.line(df, x="Input", y=["GoIsPrime", "CIsPrime"], 
              labels={"value": "Time (s)", "variable": "Method"},
              title="Prime Number Calculations Time Comparison")
fig.show()
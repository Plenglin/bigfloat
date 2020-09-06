window.BENCHMARK_DATA = {
  "lastUpdate": 1599372480310,
  "repoUrl": "https://github.com/Plenglin/bigfloat",
  "entries": {
    "Benchmark": [
      {
        "commit": {
          "author": {
            "email": "astrid@astrid.tech",
            "name": "Astrid Yu",
            "username": "Plenglin"
          },
          "committer": {
            "email": "astrid@astrid.tech",
            "name": "Astrid Yu",
            "username": "Plenglin"
          },
          "distinct": true,
          "id": "4cd1cb619b11407aab27be8328b22490fa567a54",
          "message": "CI benchmarking",
          "timestamp": "2020-09-05T23:06:52-07:00",
          "tree_id": "3ba8100236fccc947a7bd4494bcccca7dde8cceb",
          "url": "https://github.com/Plenglin/bigfloat/commit/4cd1cb619b11407aab27be8328b22490fa567a54"
        },
        "date": 1599372479965,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 7.1930386397452,
            "unit": "ns/iter",
            "extra": "iterations: 93043626\ncpu: 7.1923517146677 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.6842787070000043,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 0.6840864560000001 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.0771487298193025,
            "unit": "ns/iter",
            "extra": "iterations: 345342173\ncpu: 2.0769369891003735 ns\nthreads: undefined"
          }
        ]
      }
    ]
  }
}
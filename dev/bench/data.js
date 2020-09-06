window.BENCHMARK_DATA = {
  "lastUpdate": 1599424816811,
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
      },
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
          "id": "30fb339180c65b53f62ab1f4681e278369da856d",
          "message": "Fix CTest configuration",
          "timestamp": "2020-09-06T01:05:32-07:00",
          "tree_id": "701c5d6ecd07983aa3e4c9aac52a8943e3504e38",
          "url": "https://github.com/Plenglin/bigfloat/commit/30fb339180c65b53f62ab1f4681e278369da856d"
        },
        "date": 1599379597197,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 10.497548852414816,
            "unit": "ns/iter",
            "extra": "iterations: 66964960\ncpu: 10.448483221672946 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.8511153257107166,
            "unit": "ns/iter",
            "extra": "iterations: 821747756\ncpu: 0.851092918591432 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 3.617471543825276,
            "unit": "ns/iter",
            "extra": "iterations: 193577055\ncpu: 3.616405911330763 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 9.538719440322744,
            "unit": "ns/iter",
            "extra": "iterations: 73063272\ncpu: 9.53854589211389 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.8510161386087244,
            "unit": "ns/iter",
            "extra": "iterations: 822429630\ncpu: 0.8509489632565889 ns\nthreads: undefined"
          }
        ]
      },
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
          "id": "b76b390a9a063e65c894cad8e13fb73c8fa93b66",
          "message": "Add checking for the weird cases",
          "timestamp": "2020-09-06T13:38:48-07:00",
          "tree_id": "a119e50671943d4a704ad01f54803729c225e0e8",
          "url": "https://github.com/Plenglin/bigfloat/commit/b76b390a9a063e65c894cad8e13fb73c8fa93b66"
        },
        "date": 1599424816425,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 8.78789587767116,
            "unit": "ns/iter",
            "extra": "iterations: 81368791\ncpu: 8.78728439015396 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7217928814732099,
            "unit": "ns/iter",
            "extra": "iterations: 906300469\ncpu: 0.7216266441102328 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.924100530208267,
            "unit": "ns/iter",
            "extra": "iterations: 255254181\ncpu: 2.9239155733946625 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 8.859315025124497,
            "unit": "ns/iter",
            "extra": "iterations: 81237403\ncpu: 8.859019791659271 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7100964967745576,
            "unit": "ns/iter",
            "extra": "iterations: 900862339\ncpu: 0.7097793151279683 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 37.64079748064807,
            "unit": "ns/iter",
            "extra": "iterations: 18880107\ncpu: 37.6391748203546 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.5809534522815576,
            "unit": "ns/iter",
            "extra": "iterations: 463989681\ncpu: 1.580865333942631 ns\nthreads: undefined"
          }
        ]
      }
    ]
  }
}
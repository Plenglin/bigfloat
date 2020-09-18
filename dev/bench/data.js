window.BENCHMARK_DATA = {
  "lastUpdate": 1600410435927,
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
          "distinct": false,
          "id": "410065b501bd82aacfd9635a03adad80919c0d27",
          "message": "y e e t the fancy mul",
          "timestamp": "2020-09-17T23:25:23-07:00",
          "tree_id": "8a1b8f7116978876be97470f2c5ff58c217d154e",
          "url": "https://github.com/Plenglin/bigfloat/commit/410065b501bd82aacfd9635a03adad80919c0d27"
        },
        "date": 1600410435557,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_construction",
            "value": 5.007744801553022,
            "unit": "ns/iter",
            "extra": "iterations: 141290515\ncpu: 5.0064695991801 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_addition",
            "value": 5.6120719276375715,
            "unit": "ns/iter",
            "extra": "iterations: 122701597\ncpu: 5.608057089917093 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 1.9580919410399111,
            "unit": "ns/iter",
            "extra": "iterations: 357600480\ncpu: 1.9579406213324992 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 7.23725643002599,
            "unit": "ns/iter",
            "extra": "iterations: 96871187\ncpu: 7.231525758015127 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 2.013012905981625,
            "unit": "ns/iter",
            "extra": "iterations: 346749758\ncpu: 2.0130172174482097 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 56.9074988183432,
            "unit": "ns/iter",
            "extra": "iterations: 12869641\ncpu: 56.87307820008346 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.62563386049749,
            "unit": "ns/iter",
            "extra": "iterations: 433328589\ncpu: 1.6250013174182696 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 39.104926958599094,
            "unit": "ns/iter",
            "extra": "iterations: 18285520\ncpu: 39.07658513402954 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 11.104008388891126,
            "unit": "ns/iter",
            "extra": "iterations: 59567349\ncpu: 11.101576956194572 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.213578746948394,
            "unit": "ns/iter",
            "extra": "iterations: 217907117\ncpu: 3.212576879717063 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_nbody",
            "value": 12303.737547354965,
            "unit": "ns/iter",
            "extra": "iterations: 57016\ncpu: 12299.253104391759 ns\nthreads: undefined"
          },
          {
            "name": "double_nbody",
            "value": 633.1364705738729,
            "unit": "ns/iter",
            "extra": "iterations: 1146804\ncpu: 633.1380445132733 ns\nthreads: undefined"
          }
        ]
      }
    ]
  }
}
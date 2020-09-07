window.BENCHMARK_DATA = {
  "lastUpdate": 1599496818975,
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
          "id": "eacfc7efc4a28bda5ad3769140595133b03ccfda",
          "message": "Move MPFR integration to a different header",
          "timestamp": "2020-09-06T13:59:42-07:00",
          "tree_id": "0bb239c138c7bb310a33cd2bb5de6bab9aa5113e",
          "url": "https://github.com/Plenglin/bigfloat/commit/eacfc7efc4a28bda5ad3769140595133b03ccfda"
        },
        "date": 1599426058823,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 8.573721560293128,
            "unit": "ns/iter",
            "extra": "iterations: 82464546\ncpu: 8.572032761812574 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7675929630262887,
            "unit": "ns/iter",
            "extra": "iterations: 910221901\ncpu: 0.7674141648674745 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.784434793144027,
            "unit": "ns/iter",
            "extra": "iterations: 255479907\ncpu: 2.7839316537718943 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 9.130213238348588,
            "unit": "ns/iter",
            "extra": "iterations: 78215012\ncpu: 9.124880412982618 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7092600696303752,
            "unit": "ns/iter",
            "extra": "iterations: 940840096\ncpu: 0.7091391564162248 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 36.531880180590775,
            "unit": "ns/iter",
            "extra": "iterations: 19309693\ncpu: 36.52516137879558 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.598678096057633,
            "unit": "ns/iter",
            "extra": "iterations: 441783235\ncpu: 1.5984217622019996 ns\nthreads: undefined"
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
          "id": "e771d00395365c9e7da11773a1c4102023149f06",
          "message": "Raise precision on op tests",
          "timestamp": "2020-09-06T15:53:43-07:00",
          "tree_id": "f4f180efbd799d8dc2328043dac91e21b001b3c7",
          "url": "https://github.com/Plenglin/bigfloat/commit/e771d00395365c9e7da11773a1c4102023149f06"
        },
        "date": 1599432871575,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 9.508632456174919,
            "unit": "ns/iter",
            "extra": "iterations: 81102410\ncpu: 9.505334292778723 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7339931388015973,
            "unit": "ns/iter",
            "extra": "iterations: 979021390\ncpu: 0.7336275676264845 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.9025547483681593,
            "unit": "ns/iter",
            "extra": "iterations: 251121092\ncpu: 2.9006958364134534 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 9.749132941795411,
            "unit": "ns/iter",
            "extra": "iterations: 80041916\ncpu: 9.746875911865974 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.6835004619999836,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 0.6835021929999998 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 37.85997291793836,
            "unit": "ns/iter",
            "extra": "iterations: 17941765\ncpu: 37.823659545200854 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 4.877722948703034,
            "unit": "ns/iter",
            "extra": "iterations: 147699211\ncpu: 4.875336585244183 ns\nthreads: undefined"
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
          "id": "e91c14d2289a2452f134ea910e8a9aa7d683ddb4",
          "message": "(possibly) Optimize addition a bit",
          "timestamp": "2020-09-06T20:03:42-07:00",
          "tree_id": "4bac64c7979e7af3af69c58857e039b3d1d82c88",
          "url": "https://github.com/Plenglin/bigfloat/commit/e91c14d2289a2452f134ea910e8a9aa7d683ddb4"
        },
        "date": 1599447892019,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 9.214135707766468,
            "unit": "ns/iter",
            "extra": "iterations: 73952024\ncpu: 9.211128596020577 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7580590942220018,
            "unit": "ns/iter",
            "extra": "iterations: 963555151\ncpu: 0.7580175584573259 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.9729098313510556,
            "unit": "ns/iter",
            "extra": "iterations: 223053281\ncpu: 2.9728219734189865 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 9.449508797421204,
            "unit": "ns/iter",
            "extra": "iterations: 76354648\ncpu: 9.449534414722205 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7389558081677776,
            "unit": "ns/iter",
            "extra": "iterations: 950287437\ncpu: 0.7389240756636459 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 42.817244267062,
            "unit": "ns/iter",
            "extra": "iterations: 17657219\ncpu: 42.81670635675978 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.6677356105357477,
            "unit": "ns/iter",
            "extra": "iterations: 425396830\ncpu: 1.6676215429249908 ns\nthreads: undefined"
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
          "id": "2ffeea652f09fc6e429dfa84a7b09c852ef845cf",
          "message": "Surround with namespace, rename bigfloat -> bf\n\nboyfriend float",
          "timestamp": "2020-09-07T08:57:50-07:00",
          "tree_id": "23128692d0f582655efb04bb66f75fb7935679f5",
          "url": "https://github.com/Plenglin/bigfloat/commit/2ffeea652f09fc6e429dfa84a7b09c852ef845cf"
        },
        "date": 1599494353913,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 9.158538240731328,
            "unit": "ns/iter",
            "extra": "iterations: 77176976\ncpu: 9.158557650665143 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7332096651140778,
            "unit": "ns/iter",
            "extra": "iterations: 977266437\ncpu: 0.7327738597043418 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.9070895300937973,
            "unit": "ns/iter",
            "extra": "iterations: 248582103\ncpu: 2.906942278945962 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 9.181346419882505,
            "unit": "ns/iter",
            "extra": "iterations: 75920804\ncpu: 9.180661429770948 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7105400169999995,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 0.7104800150000004 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 37.870588593135736,
            "unit": "ns/iter",
            "extra": "iterations: 18246645\ncpu: 37.86658232239406 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.5732455592140453,
            "unit": "ns/iter",
            "extra": "iterations: 434723891\ncpu: 1.5727829667406061 ns\nthreads: undefined"
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
          "id": "747a40bc3f1dc60b2da3949b8a8c8551b11066e7",
          "message": "Make a bunch of headers",
          "timestamp": "2020-09-07T09:39:12-07:00",
          "tree_id": "7ad121576f7a9e3231d077d9754af573832e721c",
          "url": "https://github.com/Plenglin/bigfloat/commit/747a40bc3f1dc60b2da3949b8a8c8551b11066e7"
        },
        "date": 1599496818546,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 16.769513404430672,
            "unit": "ns/iter",
            "extra": "iterations: 39517643\ncpu: 16.76532509795688 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7564734204806186,
            "unit": "ns/iter",
            "extra": "iterations: 941031371\ncpu: 0.7564923348341805 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.987138931871008,
            "unit": "ns/iter",
            "extra": "iterations: 226599064\ncpu: 2.9867819312792925 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 16.661904307438153,
            "unit": "ns/iter",
            "extra": "iterations: 42194773\ncpu: 16.66176673115411 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7751970437006666,
            "unit": "ns/iter",
            "extra": "iterations: 926307587\ncpu: 0.7751513893192375 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 45.74317801933401,
            "unit": "ns/iter",
            "extra": "iterations: 15219920\ncpu: 45.74329635109775 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.6887894198238251,
            "unit": "ns/iter",
            "extra": "iterations: 428381763\ncpu: 1.6886526189491395 ns\nthreads: undefined"
          }
        ]
      }
    ]
  }
}
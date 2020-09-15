window.BENCHMARK_DATA = {
  "lastUpdate": 1600162366520,
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
          "id": "e7e0a8c8d049d11c15517da6709a99b7b0722ec9",
          "message": "attempt optimizations, make benchmark more accurate",
          "timestamp": "2020-09-07T10:55:51-07:00",
          "tree_id": "508c8ef73c4f376d820416a6099be6d7a4ea2340",
          "url": "https://github.com/Plenglin/bigfloat/commit/e7e0a8c8d049d11c15517da6709a99b7b0722ec9"
        },
        "date": 1599501445340,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 20.75007531091017,
            "unit": "ns/iter",
            "extra": "iterations: 32687827\ncpu: 20.64196460657969 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7669682759962696,
            "unit": "ns/iter",
            "extra": "iterations: 922095813\ncpu: 0.7667177618992181 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 3.138175866252392,
            "unit": "ns/iter",
            "extra": "iterations: 226680352\ncpu: 3.1368161542293715 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 19.590184502909644,
            "unit": "ns/iter",
            "extra": "iterations: 36831777\ncpu: 19.589414705676568 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7817913738265432,
            "unit": "ns/iter",
            "extra": "iterations: 813929610\ncpu: 0.7815604066793933 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 52.15723683021818,
            "unit": "ns/iter",
            "extra": "iterations: 13060884\ncpu: 52.1490765096758 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 5.7143590509909306,
            "unit": "ns/iter",
            "extra": "iterations: 131691997\ncpu: 5.713720675068815 ns\nthreads: undefined"
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
          "id": "70793ee17f2636da067fb8c2b5703d72ac6d9cf5",
          "message": "MOAR benchmarks (and shoddy attempts at optimization)",
          "timestamp": "2020-09-07T11:40:06-07:00",
          "tree_id": "419e3b5d7fc2c9bc056ecb8e251d36b00440524b",
          "url": "https://github.com/Plenglin/bigfloat/commit/70793ee17f2636da067fb8c2b5703d72ac6d9cf5"
        },
        "date": 1599504067347,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 18.939526953719845,
            "unit": "ns/iter",
            "extra": "iterations: 35586962\ncpu: 18.91811621908046 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7348421522918877,
            "unit": "ns/iter",
            "extra": "iterations: 969617721\ncpu: 0.7337193592813882 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.9949902960618533,
            "unit": "ns/iter",
            "extra": "iterations: 241823472\ncpu: 2.992977687459552 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 18.010427639415195,
            "unit": "ns/iter",
            "extra": "iterations: 39162363\ncpu: 18.010481006981117 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7247064917591454,
            "unit": "ns/iter",
            "extra": "iterations: 985229066\ncpu: 0.7244584123952351 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 50.16203576428211,
            "unit": "ns/iter",
            "extra": "iterations: 14528126\ncpu: 50.15890562898477 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.6922873237211593,
            "unit": "ns/iter",
            "extra": "iterations: 416961828\ncpu: 1.6913522021493048 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 33.00576825634204,
            "unit": "ns/iter",
            "extra": "iterations: 20495275\ncpu: 33.00586076546908 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 9.913484867712357,
            "unit": "ns/iter",
            "extra": "iterations: 70549843\ncpu: 9.911307357551447 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.027327232548155,
            "unit": "ns/iter",
            "extra": "iterations: 236649320\ncpu: 3.0273373656852276 ns\nthreads: undefined"
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
          "id": "54ce110153b6582b6b72e91acc348d458afe9800",
          "message": "Create file for simd tests",
          "timestamp": "2020-09-07T12:05:37-07:00",
          "tree_id": "e5845971f98cda52a18eebc32dcd30c5998e144b",
          "url": "https://github.com/Plenglin/bigfloat/commit/54ce110153b6582b6b72e91acc348d458afe9800"
        },
        "date": 1599505605966,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 18.865119493720616,
            "unit": "ns/iter",
            "extra": "iterations: 36785071\ncpu: 18.86305958197009 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.8053657536872596,
            "unit": "ns/iter",
            "extra": "iterations: 870215793\ncpu: 0.8052527506818071 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 3.4381497104789682,
            "unit": "ns/iter",
            "extra": "iterations: 204345923\ncpu: 3.4369637264551645 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 17.950062340611407,
            "unit": "ns/iter",
            "extra": "iterations: 38468503\ncpu: 17.94965852973274 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.78133612767176,
            "unit": "ns/iter",
            "extra": "iterations: 870164225\ncpu: 0.7813367045743579 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 49.95587031613731,
            "unit": "ns/iter",
            "extra": "iterations: 13317000\ncpu: 49.95414590373203 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.4855031371969198,
            "unit": "ns/iter",
            "extra": "iterations: 462425222\ncpu: 1.4855035978119717 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 36.40062638179931,
            "unit": "ns/iter",
            "extra": "iterations: 19793040\ncpu: 36.39922664734676 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 10.39340568285704,
            "unit": "ns/iter",
            "extra": "iterations: 70658931\ncpu: 10.39252006232587 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.032181036949949,
            "unit": "ns/iter",
            "extra": "iterations: 234265944\ncpu: 3.0291780396385732 ns\nthreads: undefined"
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
          "id": "85f59ae2d2c3e7c06157e82ba5f2407e22acfcaa",
          "message": "Get comparisons working",
          "timestamp": "2020-09-07T12:21:35-07:00",
          "tree_id": "40219438422973b2ad202dd43df6929ea79de907",
          "url": "https://github.com/Plenglin/bigfloat/commit/85f59ae2d2c3e7c06157e82ba5f2407e22acfcaa"
        },
        "date": 1599506556266,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_addition",
            "value": 17.132047826941495,
            "unit": "ns/iter",
            "extra": "iterations: 39662917\ncpu: 17.100098437036287 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.6940487260000054,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 0.6938896969999999 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_construction",
            "value": 2.7043971858678786,
            "unit": "ns/iter",
            "extra": "iterations: 258255674\ncpu: 2.704222401711879 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 16.635134076970377,
            "unit": "ns/iter",
            "extra": "iterations: 42935114\ncpu: 16.634967756228626 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.6757257170000059,
            "unit": "ns/iter",
            "extra": "iterations: 1000000000\ncpu: 0.6756609259999998 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 46.0342750926801,
            "unit": "ns/iter",
            "extra": "iterations: 15326173\ncpu: 46.03398480494774 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 4.778367753277965,
            "unit": "ns/iter",
            "extra": "iterations: 148239489\ncpu: 4.778245599591888 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 30.533955634998282,
            "unit": "ns/iter",
            "extra": "iterations: 23021525\ncpu: 30.532701678103432 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 9.810714993860365,
            "unit": "ns/iter",
            "extra": "iterations: 72094675\ncpu: 9.810623738854499 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.044013603088446,
            "unit": "ns/iter",
            "extra": "iterations: 231680328\ncpu: 3.04394488771615 ns\nthreads: undefined"
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
          "id": "64b7f5afe53c82e82874fe6c8b16807c7a538087",
          "message": "Reorganize benchmarks folder",
          "timestamp": "2020-09-07T12:45:43-07:00",
          "tree_id": "4e2d01cd87bf92074ecdbed6845b3d9fdfe4d22d",
          "url": "https://github.com/Plenglin/bigfloat/commit/64b7f5afe53c82e82874fe6c8b16807c7a538087"
        },
        "date": 1599508002259,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_construction",
            "value": 3.6732479152062694,
            "unit": "ns/iter",
            "extra": "iterations: 192202841\ncpu: 3.672898170116018 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_addition",
            "value": 19.471263791634446,
            "unit": "ns/iter",
            "extra": "iterations: 33713825\ncpu: 19.453867664081418 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7265523850136489,
            "unit": "ns/iter",
            "extra": "iterations: 924065913\ncpu: 0.7263056569428944 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 18.26976001816864,
            "unit": "ns/iter",
            "extra": "iterations: 38729557\ncpu: 18.268059095021417 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7538148725618036,
            "unit": "ns/iter",
            "extra": "iterations: 930089195\ncpu: 0.7534537115012934 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 51.2266113355621,
            "unit": "ns/iter",
            "extra": "iterations: 12536650\ncpu: 51.2260272082255 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 5.122606239999641,
            "unit": "ns/iter",
            "extra": "iterations: 100000000\ncpu: 5.121483209999997 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 35.68974506303691,
            "unit": "ns/iter",
            "extra": "iterations: 19481914\ncpu: 35.6857417089512 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 11.442582484436468,
            "unit": "ns/iter",
            "extra": "iterations: 64841111\ncpu: 11.442324623339662 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.4488465949498948,
            "unit": "ns/iter",
            "extra": "iterations: 199428943\ncpu: 3.448555774574809 ns\nthreads: undefined"
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
          "id": "da4365abb49b4460c67b3c9a758a592db86599fd",
          "message": "Add a janky bootleg sqrt and nbody sim",
          "timestamp": "2020-09-07T13:34:27-07:00",
          "tree_id": "d3cb821f9c44f4d54aa0521d5500bb9256073232",
          "url": "https://github.com/Plenglin/bigfloat/commit/da4365abb49b4460c67b3c9a758a592db86599fd"
        },
        "date": 1599511118968,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_construction",
            "value": 2.995662825219394,
            "unit": "ns/iter",
            "extra": "iterations: 224657075\ncpu: 2.995113490193887 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_addition",
            "value": 18.993775236732315,
            "unit": "ns/iter",
            "extra": "iterations: 36579865\ncpu: 18.992198276292168 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 0.7535336977253695,
            "unit": "ns/iter",
            "extra": "iterations: 937842455\ncpu: 0.7534668080258748 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 18.3630680024209,
            "unit": "ns/iter",
            "extra": "iterations: 38256241\ncpu: 18.33270095721114 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 0.7508005877589972,
            "unit": "ns/iter",
            "extra": "iterations: 928974671\ncpu: 0.7507727969043846 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 51.380507157748504,
            "unit": "ns/iter",
            "extra": "iterations: 13712972\ncpu: 51.36883886293945 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 5.313055004476833,
            "unit": "ns/iter",
            "extra": "iterations: 133191268\ncpu: 5.313013748018377 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 33.8547765903674,
            "unit": "ns/iter",
            "extra": "iterations: 20599537\ncpu: 33.844282616643284 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 11.272213251825962,
            "unit": "ns/iter",
            "extra": "iterations: 62493214\ncpu: 11.252174196065507 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.408304098675803,
            "unit": "ns/iter",
            "extra": "iterations: 206351257\ncpu: 3.4075888522452815 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_nbody",
            "value": 20253.16949683804,
            "unit": "ns/iter",
            "extra": "iterations: 35098\ncpu: 20248.03589948148 ns\nthreads: undefined"
          },
          {
            "name": "double_nbody",
            "value": 1155.6917874599824,
            "unit": "ns/iter",
            "extra": "iterations: 615997\ncpu: 1155.487891986485 ns\nthreads: undefined"
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
          "id": "ac6543098f7fb2fb182ea10d5a4cdf9f1f20cd65",
          "message": "Fix inf acting up during compile?",
          "timestamp": "2020-09-15T02:31:17-07:00",
          "tree_id": "48bb6725bd2d83898644c7b3432a4f77984046d8",
          "url": "https://github.com/Plenglin/bigfloat/commit/ac6543098f7fb2fb182ea10d5a4cdf9f1f20cd65"
        },
        "date": 1600162366015,
        "tool": "googlecpp",
        "benches": [
          {
            "name": "bigfloat_construction",
            "value": 4.686748794678435,
            "unit": "ns/iter",
            "extra": "iterations: 145300405\ncpu: 4.68645901571988 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_addition",
            "value": 6.286465676380257,
            "unit": "ns/iter",
            "extra": "iterations: 111870282\ncpu: 6.285942713543888 ns\nthreads: undefined"
          },
          {
            "name": "double_addition",
            "value": 1.586420445708301,
            "unit": "ns/iter",
            "extra": "iterations: 445337665\ncpu: 1.5862722278386228 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_multiplication",
            "value": 8.431546667142015,
            "unit": "ns/iter",
            "extra": "iterations: 82197298\ncpu: 8.431398316767055 ns\nthreads: undefined"
          },
          {
            "name": "double_multiplication",
            "value": 1.6007552430512506,
            "unit": "ns/iter",
            "extra": "iterations: 435046174\ncpu: 1.6005867597861005 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_division",
            "value": 50.90627739127156,
            "unit": "ns/iter",
            "extra": "iterations: 13772632\ncpu: 50.90499985768878 ns\nthreads: undefined"
          },
          {
            "name": "double_division",
            "value": 1.7948505956205951,
            "unit": "ns/iter",
            "extra": "iterations: 374575399\ncpu: 1.7946637200271653 ns\nthreads: undefined"
          },
          {
            "name": "int128_division",
            "value": 35.58784787498494,
            "unit": "ns/iter",
            "extra": "iterations: 19849911\ncpu: 35.58468372981621 ns\nthreads: undefined"
          },
          {
            "name": "int64_division",
            "value": 10.531272137652545,
            "unit": "ns/iter",
            "extra": "iterations: 64872508\ncpu: 10.530297857452977 ns\nthreads: undefined"
          },
          {
            "name": "int32_division",
            "value": 3.144896053721048,
            "unit": "ns/iter",
            "extra": "iterations: 220771299\ncpu: 3.1446483403623997 ns\nthreads: undefined"
          },
          {
            "name": "bigfloat_nbody",
            "value": 11075.791407566872,
            "unit": "ns/iter",
            "extra": "iterations: 63521\ncpu: 11075.352151257079 ns\nthreads: undefined"
          },
          {
            "name": "double_nbody",
            "value": 659.053377552319,
            "unit": "ns/iter",
            "extra": "iterations: 1025506\ncpu: 659.0057903122959 ns\nthreads: undefined"
          }
        ]
      }
    ]
  }
}
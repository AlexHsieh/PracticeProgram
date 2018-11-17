import UIKit

func caculatePi(sample: Int) {
    let closedRange = -1.0...1.0
    let r = 1.0
    var n = 0.0
    for _ in 1...sample {
        let x = Double.random(in: closedRange)
        let y = Double.random(in: closedRange)
        if x * x + y * y <= r * r {
            n += 1
        }
    }
    
    // caculaye pi
    let N = Double(sample)
    print("pi: \(4 * n / N)")
}

caculatePi(sample: 10000)
caculatePi(sample: 50000)
caculatePi(sample: 100000)


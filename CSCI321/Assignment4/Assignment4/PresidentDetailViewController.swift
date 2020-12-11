//
//  PresidentDetailViewController.swift
//  Assignment4
//
//  Created by Robbie Korneta on 11/5/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit

class PresidentDetailViewController: UIViewController {

    @IBOutlet weak var presidentNameLabel: UILabel!
    @IBOutlet weak var presidentNumberLabel: UILabel!
    @IBOutlet weak var presidencyDatesLabel: UILabel!
    @IBOutlet weak var nickamesLabel: UILabel!
    @IBOutlet weak var politicalPartyLabel: UILabel!
    
    var presidentName = ""  // Name of president
    var number = 0          // President number
    var startDate = ""      // Start date of presidency
    var endDate = ""        // End date of presidency
    var nicknames = ""      // Nicknames of president
    var politicalParty = "" // Political party of president
    
    let numberFormatter = NumberFormatter() // Format number
    
    // Handles the UI when the view is loading
    override func viewDidLoad() {
        
        super.viewDidLoad()

        numberFormatter.numberStyle = .ordinal // Set number formatter to 1st, 2nd, etc.
        
        // Set labels to their respective values
        presidentNameLabel.text = presidentName
        presidentNumberLabel.text = "\(numberFormatter.string(from: NSNumber(value: number)) ?? "0") President of the United States"
        presidencyDatesLabel.text = "(\(startDate) to \(endDate))"
        nickamesLabel.text = nicknames
        politicalPartyLabel.text = politicalParty
        // Do any additional setup after loading the view.
    }

}

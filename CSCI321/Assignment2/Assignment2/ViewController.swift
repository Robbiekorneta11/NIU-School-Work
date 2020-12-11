//
//  ViewController.swift
//  Assignment2
//
//  Created by Robbie Korneta on 10/6/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//
// App icon and launch screen were created for extra credit

import UIKit

class ViewController: UIViewController {
    
    @IBOutlet weak var billTextField: UITextField!
    @IBOutlet weak var tipPercentageLabel: UILabel!
    @IBOutlet weak var partySizeLabel: UILabel!
    @IBOutlet weak var tipSlider: UISlider!
    @IBOutlet weak var partySizeSlider: UISlider!
    @IBOutlet weak var totalBillLabel: UILabel!
    @IBOutlet weak var pricePerPersonLabel: UILabel!
    
    var array: [Any] = []
    
    var obj: [String: Int] = ["Mary": 28, "John": 30, "Sanjay": 46]
    
    let numberFormatter = NumberFormatter() //Number formatter
    
    var tipPercentage = 20.00   //The user specified tip percentage
    var tipAmount = 0.00        //The converted amount of the tip
    var partySize = 1           //Size of the party
    var pricePerPerson = 0.00   //Price per person based on party size
    var billAmount = 0.00 {     //Total bill amount
        
        didSet {
            
            updateView()
            
        }
        
    }
    
    override func viewDidLoad() {
        
        super.viewDidLoad()
        
        billTextField.delegate = self //Set up delegate
        
        // Do any additional setup after loading the view.
    }
    
    // MARK: UIResponder methods

    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        
        self.view.endEditing(true)
        
    }
    
    /*
    *   Update view updates the view controller with the user specified values
    */
    
    func updateView() {
        
        numberFormatter.numberStyle = .currency //Format the numbers to currency style
        
        //billAmount = Double(billTextField.text!) ?? 0.00
        
        totalBillLabel.text = numberFormatter.string(from: NSNumber(value: billAmount + tipAmount)) //Update bill label
        tipPercentageLabel.text = "\(Int(tipPercentage))%" //Update Tip percentage label
        partySizeLabel.text = "\(partySize)" //Update party size label
        pricePerPersonLabel.text = numberFormatter.string(from: NSNumber(value: (billAmount + tipAmount) / Double(partySize))) //Update price per person label
        
    }
    
    /*
     *  Calculates the bill amount, tip amount, and price per person
     *  when the calculate button is pressed
     */
    
    @IBAction func calculate(_ sender: Any) {
        
        billAmount = Double(billTextField.text!) ?? 0.00 //Bill amount is the text field
        tipAmount = billAmount * (tipPercentage / 100)   //Tip amount is the bill amount multiplied by the tip percentage
        pricePerPerson = billAmount / Double(partySize) //Price per person is the bill amount divided by the party size
        self.view.endEditing(true) //Dismiss keyboard
        
        updateView() //Update the view
        
    }
    
    /*
     *  Function to hanlde when the tip slider is interacted with
     */
    
    @IBAction func onTipSlide(_ sender: UISlider) {
        
        /*
         *  Based on the slider position, it will increment the tip amount
         *  by 5 for each range of slider values
         */
        
        if (sender.value <= 0) {
            
            tipPercentage = 0.00
            
        } else if (sender.value > 0 && sender.value < 5.714) {
            
            tipPercentage = 5.00
            
        } else if (sender.value >= 5.714 && sender.value < 11.428) {
            
            tipPercentage = 10.00
            
        } else if (sender.value >= 11.428 && sender.value < 17.142) {
            
            tipPercentage = 15.00
            
        } else if (sender.value >= 17.142 && sender.value < 22.856) {
            
            tipPercentage = 20.00
            
        } else if (sender.value >= 22.856 && sender.value < 28.57) {
            
            tipPercentage = 25.00
            
        } else if (sender.value >= 28.57 && sender.value < 34.284) {
            
            tipPercentage = 30.00
            
        } else if (sender.value >= 34.284 && sender.value < 40) {
            
            tipPercentage = 35.00
            
        } else if (sender.value == 40) {
            
            tipPercentage = 40.00
            
        } else {
            
            tipPercentage = 0
            
        }
        
        billAmount = Double(billTextField.text!) ?? 0.00 //Get bill value
        tipPercentageLabel.text = "\(Int(tipPercentage))%" //Update tip label
        tipAmount = billAmount * (tipPercentage / 100) //Calculate tip amount
        
        updateView() //Update the view
        
    }
    
    /*
     *  Handles party size sliding
     */
    
    @IBAction func onPartySlide(_ sender: Any) {
        
        partySizeLabel.text = "\(Int(partySizeSlider.value))" //Update party size label in increments of 1
        
        partySize = Int(partySizeSlider.value) //Set party size
        pricePerPerson = billAmount / Double(partySize) //Calculate price per person
        
        updateView() //Update view
        
    }
    
}

extension ViewController: UITextFieldDelegate {
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {

        billAmount = Double(textField.text!) ?? 0.00 //Update bill amount
        updateView() //Update view
        
        return true
        
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        
        textField.resignFirstResponder()
        return true
        
    }
    
}


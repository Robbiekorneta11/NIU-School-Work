//
//  TemperatureViewController.swift
//  Assignment3
//
//  Created by Robbie Korneta on 10/15/20.
//  Copyright © 2020 Robbie Korneta. All rights reserved.
//

import UIKit

class TemperatureViewController: UIViewController {
    
    @IBOutlet weak var tempConversionSegControl: UISegmentedControl! // Segmented control to select conversion (f -> c or c -> f)
    @IBOutlet weak var temperaturePicker: UIPickerView! // Choose the temperature to convert
    @IBOutlet weak var temperatureLabel: UILabel! // Label to display the converted temperature
    
    var fahrenheitTemps: [Int] = [] //Array of farenheit values
    var celciusTemps: [Int] = [] // Array of celcius values
    
    /*
     *  Loading UI Components when the view is brought up. Populates array values
     */
    
    override func viewDidLoad() {
        
        super.viewDidLoad()

        fahrenheitTemps += -129...134 //Populate arrays with values
        celciusTemps += -90...57
        temperaturePicker.delegate = self //Set delegate to the view model
        temperaturePicker.dataSource = self //Set data source to the view model
        temperaturePicker.reloadAllComponents() //Reload the picker view
        
        tempConversionSegControl.setTitle("\u{2109} \u{2B62} \u{2103}", forSegmentAt: 0) //Set the titles of the segemented controller
        tempConversionSegControl.setTitle("\u{2103} \u{2B62} \u{2109}", forSegmentAt: 1)
        
        temperatureLabel.text = "\(celciusTemps[0]) \u{2103}" //Set text of the temperature label
        // Do any additional setup after loading the view.
    }
    
    /*
     *  Convert temp takes a value and converts it to either celcius or farenheit
     *
     *  @param fOrC - An integer representing whether it is farenheit or celcius
     *  @param Temp - An integer containing the temperature to convert
     */
    
    func convertTemp(fOrC: Int, Temp: Int) {
        
        var convertedTemp = 0 //Converted temp variable
        
        if fOrC == 0 { //This means we are going farenheit to celcius
            
            convertedTemp = Int(Double(Temp - 32) * (5/9)) //Doing the conversion
            
            temperatureLabel.text = "\(convertedTemp) \u{2103}" //Updating the label with the converted temperature
            
        } else {
            
            convertedTemp = Int(Double(Temp * (9/5)) + 32) //Converting the temperature to farenheit
            
            temperatureLabel.text = "\(convertedTemp) \u{2109}" //Updating the label with the converted temperature
            
        }
        
    }
    
    /*
     *  Handles the segmeneted controller being switched
     */
    
    @IBAction func tempIndexChanged(_ sender: Any) {
        
        temperaturePicker.reloadAllComponents() //Reload the picker view
        convertTemp(fOrC: tempConversionSegControl.selectedSegmentIndex, Temp: temperaturePicker.selectedRow(inComponent: 0)) //Convert current temp to either farenheit or celcius
        
    }

}

extension TemperatureViewController: UIPickerViewDelegate, UIPickerViewDataSource {
    
    //Number or sections in the picker view
    
    func numberOfComponents(in pickerView: UIPickerView) -> Int {
        
        return 1
        
    }
    
    //Number of rows in the picker view
    
    func pickerView(_ pickerView: UIPickerView, numberOfRowsInComponent component: Int) -> Int {
        
        //If the segemented control is f -> c
        if tempConversionSegControl.selectedSegmentIndex == 0 {
            
            return fahrenheitTemps.count
            
        } else { // if the segmented control is c -> f
            
            return celciusTemps.count
            
        }
        
    }
    
    //Setting the title for the picker view
    
    func pickerView(_ pickerView: UIPickerView, titleForRow row: Int, forComponent component: Int) -> String? {
    
        if tempConversionSegControl.selectedSegmentIndex == 0 { //Setting title for farenheits
            
            return "\(fahrenheitTemps[row])"
            
        } else { //setting title for celcius
            
            return "\(celciusTemps[row])"
            
        }
    
    }
    
    //Handles the selected value in the picker view
    
    func pickerView(_ pickerView: UIPickerView, didSelectRow row: Int, inComponent component: Int) {
        
        if tempConversionSegControl.selectedSegmentIndex == 0 { //If it is f -> c
            
            convertTemp(fOrC: 0, Temp: fahrenheitTemps[row])
            
        } else {
            
            convertTemp(fOrC: 1, Temp: celciusTemps[row]) //if it is c -> f
            
        }
        
    }
    
}

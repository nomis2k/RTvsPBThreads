/**
 * ROOT Reader
 *
 * Created by Samvel Khalatyan on Mar 8, 2011
 * Copyright 2011, All rights reserved
 */

#include <iostream>
#include <string>

#include <TFile.h>
#include <TTree.h>

#include "interface/RTEvent.h"
#include "interface/RTReader.h"

using namespace std;

using rt::Reader;

Reader::Reader(const fs::path &input_file):
    _is_good(true),
    _events_in_tree(0),
    _events_read(0)
{
    _input.reset(new TFile(input_file.string().c_str(), "read"));
    if (!_input->IsOpen())
    {
        cerr << "Failed to open input TFile" << endl;

        _input.reset();
    }

    _input->GetObject("rt", _tree);
    if (!_tree)
    {
        cerr << "Failed to extract Tree" << endl;

        _input.reset();
    }

    _event.reset(new Event());

    Event *event = _event.get();
    _tree->SetBranchAddress("event", &event);

    _events_in_tree = _tree->GetEntries();

    cout << "File has " << _events_in_tree << " events stored" << endl;
}

Reader::~Reader()
{
    cout << "Read " << _events_read << " events" << endl;
}

bool Reader::good() const
{
    return _tree && _events_read < _events_in_tree;
}

bool Reader::read(Event *event)
{
    if (!good())
        return false;

    if (!_tree->GetEvent(_events_read))
    {
        _tree = 0;

        return false;
    }

    event = _event.get();

    ++_events_read;

    return true;
}

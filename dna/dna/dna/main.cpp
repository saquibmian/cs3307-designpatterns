//
//  main.cpp
//  dna
//
//  Created by Saquib Mian on 2014-11-13.
//  Copyright (c) 2014 Saquib Mian. All rights reserved.
//

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

#define LOG(x) (cout << (x) << endl)

enum Base { A, T, G, C };

class Sequence {
private:
    vector<Base>* _bases;
    vector<Base>::iterator _iterator;
public:
    Sequence() {
        // random sequence
        _bases = new vector<Base>;
        _bases->push_back( A );
        _bases->push_back( T );
        _bases->push_back( G );
        _bases->push_back( C );
        _iterator = _bases->begin();
    }
    Sequence( vector<Base>* bases ) {
        _bases = bases;
        _iterator = _bases->begin();
    }
    
    virtual vector<Base>* GetBases() {
        LOG( "Getting all bases" );
        return _bases;
    }

    virtual Base GetNextBase() {
        LOG( "Getting next base" );
        return *(_iterator++);
    }
    virtual long GetSize() {
        LOG( "Getting size of sequence" );
        return _bases->size();
    }
    virtual bool IsConnectedWith( Sequence* sequence ) {
        LOG( "Determining if two sequences are connected" );
        return false;
    }
    virtual void Connect( Sequence* sequence ) {
        LOG( "Connecting sequences" );
    }
};

class SequenceStreamer {
public:
    SequenceStreamer( vector<Sequence>* sequences ) {}
    SequenceStreamer( vector<SequenceStreamer>* readers ) {}
    SequenceStreamer( Sequence sequence ) {}
};

class Region : public Sequence {
private:
    Sequence* _sequence;
public:
    Region() : Sequence() {
        _sequence = this;
    }
    virtual vector<Base>* GetBases() {
        LOG( "Getting all bases" );
        return _sequence->GetBases();
    }
    virtual Base GetNextBase() {
        LOG( "Getting next base" );
        return _sequence->GetNextBase();
    }
    
    virtual SequenceStreamer* GetSequence() {
        LOG( "Getting sequence streamer of sequence" );
        return new SequenceStreamer( *_sequence );
    }
    
    virtual bool HasSubRegions() {
        LOG( "Region does not have sub regions" );
        return false;
    }
};

class Chromosome : public Region {
private:
    vector<Region>* _regions;
    vector<SequenceStreamer> streams;
public:
    SequenceStreamer* GetSequence() {
        LOG( "Getting chromosome sequence via concatentation of all regions in it" );
        streams.clear();
        for( vector<Region>::iterator it = _regions->begin(); it != _regions->end(); it++ ) {
            streams.push_back( *it->GetSequence() );
        }
        return new SequenceStreamer( &streams );
    }
    
    bool HasSubRegions() {
        LOG( "Chromosome does have sub regions" );
        return true;
    }
};

class Genome {
private:
    vector<Region>* _regions;
public:
    Genome() {
        // random regions
        _regions = new vector<Region>;
        _regions->push_back( Region() );
        _regions->push_back( Region() );
        _regions->push_back( Region() );
        _regions->push_back( Region() );

    }
    vector<Region>* GetRegions() const {
        LOG( "Getting all regions of genome" );
        return _regions;
    }
};

class Alignment {
    // not important from a design perspective
};


class SequenceReadEvent {
public:
    SequenceReadEvent() {};
    Sequence* GetSequence() {
        LOG( "Getting sequence from read event" );
        return new Sequence();
    };
};

class Handler {
protected:
    Handler* _nextHandler = NULL;
public:
    void AppendHandler( Handler* nextHandler ) {
        LOG( "Attempting to append handler somehow..." );
        // set the handler at the end of the chain
        if( _nextHandler == NULL ) {
            LOG( "Setting next handler in chain" );
            _nextHandler = nextHandler;
        } else {
            LOG( "Dispatching append handler" );
            _nextHandler->AppendHandler( nextHandler );
        }
    }
    virtual void Handle( SequenceReadEvent e ) = 0;
    
};

class RegionHandler : public Handler {
private:
    Region _region;
public:
    RegionHandler( Region region ) {
        _region = region;
    };
    void Handle( SequenceReadEvent e ) {
        LOG( "Handling at region level" );
        if( _region.IsConnectedWith( e.GetSequence() ) ) {
            _region.Connect( e.GetSequence() );
        }
        // would calculate probability here
        if( true && _nextHandler != NULL /* not found similar */ ) {
            LOG( "Dispatching to next region handler" );
            _nextHandler->Handle( e );
        }
    };
};

class GenomeHandler : public Handler {
private:
    RegionHandler* _mainHandler = NULL;
    Genome _genome;
    void Initialize() {
        LOG( "Initializing GenomeHandler with given genome" );
        for( vector<Region>::iterator it = _genome.GetRegions()->begin(); it != _genome.GetRegions()->end(); ++it ) {
            
            RegionHandler* handler = new RegionHandler( *it );
            
            if( _mainHandler == NULL ) {
                _mainHandler = handler;
            } else {
                _mainHandler->AppendHandler( handler );
            }
        }
    }
public:
    GenomeHandler( Genome genome ) {
        _genome = genome;
        Initialize();
    };
    void Handle( SequenceReadEvent e ) {
        LOG( "Handling at genome level" );
        // would calculate probability here
        if( true && _mainHandler != NULL /* not found similar */ ) {
            LOG( "Dispatching to next genome handler" );
            _mainHandler->Handle( e );
        }
    };
};

class GenomeMapper {
private:
    GenomeHandler* _mainHandler = NULL;
public:
    GenomeMapper( vector<Genome>* genomes ) {
        LOG( "Initializing GenomeMapper" );
        for( vector<Genome>::iterator it = genomes->begin(); it != genomes->end(); it++ ) {
            
            GenomeHandler* handler = new GenomeHandler( *it );
            
            if( _mainHandler == NULL ) {
                _mainHandler = handler;
            } else {
                _mainHandler->AppendHandler( handler );
            }
        }
    };
    Genome GetReferencedGenome() {
        cout << "Would return referenced genome based on probability" << endl;
        return Genome();
    };
    Alignment GetAlignment() {
        cout << "Would return alignment information from referenced genome" << endl;
        return Alignment();
    };
    void ProcessReadEvent( SequenceReadEvent e ) {
        LOG( "Processing read event" );
        _mainHandler->Handle( e );
    }
};


class Data {
public:
    vector<Genome>* GetGenomes() {
        LOG( "Getting random genomes" );
        vector<Genome>* genomes = new vector<Genome>;
        genomes->push_back( Genome() );
        genomes->push_back( Genome() );
        genomes->push_back( Genome() );
        genomes->push_back( Genome() );
        
        return genomes;
    }
};

class SequenceReader {
private:
    int _numberOfTimesExecuted = 0;
public:
    SequenceReadEvent ReadNext() {
        LOG( "Receiving new DNA read" );
        ++_numberOfTimesExecuted;
        return SequenceReadEvent();
    };
    bool CanRead() {
        // for example
        return _numberOfTimesExecuted < 5;
    }
    
};

class SequenceReadEventDispatcher {
private:
    long MINIMUM_SIZE = 2;
    GenomeMapper* _mapper;
public:
    SequenceReadEventDispatcher( Data data ) {
        _mapper = new GenomeMapper( data.GetGenomes() );
    };
    void DispatchReadEvent( SequenceReadEvent e ) {
        LOG( "Dispatcher has new event to dispatch" );
        if( e.GetSequence()->GetSize() >= MINIMUM_SIZE ) {
            _mapper->ProcessReadEvent( e );
        } else {
            cout << "Read was too small to gather enough data" << endl;
        }
    }
    
    void GetStatus() {
        Genome genome = _mapper->GetReferencedGenome();
        LOG( "Would print referenced genome up to this point" );
        Alignment alignment = _mapper->GetAlignment();
        LOG( "Would print alignment up to this point" );
    }
    
};

int main(int argc, const char * argv[]) {
    
    Data data;
    SequenceReader reader;
    SequenceReadEventDispatcher dispatcher( data );
    
    while( reader.CanRead() ) {
        SequenceReadEvent event = reader.ReadNext();

        dispatcher.DispatchReadEvent( event );
        dispatcher.GetStatus();
    }

    LOG( "Done!" );
    
    return 0;
}




//
//  EaseCollectionView.h
//  PSPDFKit
//
//  Copyright (c) 2012-2013 Peter Steinberger. All rights reserved.
//

#import "EaseCollectionViewLayout.h"
#import "EaseCollectionViewFlowLayout.h"
#import "EaseCollectionViewCell.h"
#import "EaseCollectionViewController.h"
#import "EaseCollectionViewUpdateItem.h"

@class EaseCollectionViewController;

typedef NS_OPTIONS(NSUInteger, EaseCollectionViewScrollPosition) {
    EaseCollectionViewScrollPositionNone                 = 0,

    // The vertical positions are mutually exclusive to each other, but are bitwise or-able with the horizontal scroll positions.
    // Combining positions from the same grouping (horizontal or vertical) will result in an NSInvalidArgumentException.
    EaseCollectionViewScrollPositionTop                  = 1 << 0,
    EaseCollectionViewScrollPositionCenteredVertically   = 1 << 1,
    EaseCollectionViewScrollPositionBottom               = 1 << 2,

    // Likewise, the horizontal positions are mutually exclusive to each other.
    EaseCollectionViewScrollPositionLeft                 = 1 << 3,
    EaseCollectionViewScrollPositionCenteredHorizontally = 1 << 4,
    EaseCollectionViewScrollPositionRight                = 1 << 5
};

typedef NS_ENUM(NSUInteger, PSTCollectionElementCategory) {
    PSTCollectionElementCategoryCell,
    PSTCollectionElementCategorySupplementaryView,
    PSTCollectionElementCategoryDecorationView
};

// Define the `EaseCollectionViewDisableForwardToUICollectionViewSentinel` to disable the automatic forwarding to UICollectionView on iOS 6+. (Copy below line into your AppDelegate.m)
//@interface EaseCollectionViewDisableForwardToUICollectionViewSentinel : NSObject @end @implementation EaseCollectionViewDisableForwardToUICollectionViewSentinel @end

// API-compatible replacement for UICollectionView.
// Works on iOS 4.3 upwards (including iOS 6).
@interface EaseCollectionView : UIScrollView

- (id)initWithFrame:(CGRect)frame collectionViewLayout:(EaseCollectionViewLayout *)layout; // the designated initializer

@property (nonatomic, strong) EaseCollectionViewLayout *collectionViewLayout;
@property (nonatomic, assign) IBOutlet id<EaseCollectionViewDelegate> delegate;
@property (nonatomic, assign) IBOutlet id<EaseCollectionViewDataSource> dataSource;
@property (nonatomic, strong) UIView *backgroundView; // will be automatically resized to track the size of the collection view and placed behind all cells and supplementary views.

// For each reuse identifier that the collection view will use, register either a class or a nib from which to instantiate a cell.
// If a nib is registered, it must contain exactly 1 top level object which is a EaseCollectionViewCell.
// If a class is registered, it will be instantiated via alloc/initWithFrame:
- (void)registerClass:(Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;

- (void)registerClass:(Class)viewClass forSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier;

- (void)registerNib:(UINib *)nib forCellWithReuseIdentifier:(NSString *)identifier;

// TODO: implement!
- (void)registerNib:(UINib *)nib forSupplementaryViewOfKind:(NSString *)kind withReuseIdentifier:(NSString *)identifier;

- (id)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

- (id)dequeueReusableSupplementaryViewOfKind:(NSString *)elementKind withReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

// These properties control whether items can be selected, and if so, whether multiple items can be simultaneously selected.
@property (nonatomic) BOOL allowsSelection; // default is YES
@property (nonatomic) BOOL allowsMultipleSelection; // default is NO

- (NSArray *)indexPathsForSelectedItems; // returns nil or an array of selected index paths
- (void)selectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(EaseCollectionViewScrollPosition)scrollPosition;

- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

- (void)reloadData; // discard the dataSource and delegate data and requery as necessary

- (void)setCollectionViewLayout:(EaseCollectionViewLayout *)layout animated:(BOOL)animated; // transition from one layout to another

// Information about the current state of the collection view.

- (NSInteger)numberOfSections;

- (NSInteger)numberOfItemsInSection:(NSInteger)section;

- (EaseCollectionViewLayoutAttributes *)layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;

- (EaseCollectionViewLayoutAttributes *)layoutAttributesForSupplementaryElementOfKind:(NSString *)kind atIndexPath:(NSIndexPath *)indexPath;

- (NSIndexPath *)indexPathForItemAtPoint:(CGPoint)point;

- (NSIndexPath *)indexPathForCell:(EaseCollectionViewCell *)cell;

- (EaseCollectionViewCell *)cellForItemAtIndexPath:(NSIndexPath *)indexPath;

- (NSArray *)visibleCells;

- (NSArray *)indexPathsForVisibleItems;

// Interacting with the collection view.

- (void)scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(EaseCollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;

// These methods allow dynamic modification of the current set of items in the collection view
- (void)insertSections:(NSIndexSet *)sections;
- (void)deleteSections:(NSIndexSet *)sections;
- (void)reloadSections:(NSIndexSet *)sections;
- (void)moveSection:(NSInteger)section toSection:(NSInteger)newSection;
- (void)insertItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)deleteItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)reloadItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;
- (void)performBatchUpdates:(void (^)(void))updates completion:(void (^)(BOOL finished))completion; // allows multiple insert/delete/reload/move calls to be animated simultaneously. Nestable.

@end

// To dynamically switch between EaseCollectionView and UICollectionView, use the EaseUICollectionView* classes.
#define EaseUICollectionView EaseUICollectionView_
#define EaseUICollectionViewCell EaseUICollectionViewCell_
#define EaseUICollectionReusableView EaseUICollectionReusableView_
#define EaseUICollectionViewDelegate EaseCollectionViewDelegate
#define EaseUICollectionViewDataSource EaseCollectionViewDataSource
#define EaseUICollectionViewLayout EaseUICollectionViewLayout_
#define EaseUICollectionViewFlowLayout EaseUICollectionViewFlowLayout_
#define EaseUICollectionViewDelegateFlowLayout EaseCollectionViewDelegateFlowLayout
#define EaseUICollectionViewLayoutAttributes EaseUICollectionViewLayoutAttributes_
#define EaseUICollectionViewController EaseUICollectionViewController_

@interface EaseUICollectionView_ : EaseCollectionView @end
@interface EaseUICollectionViewCell_ : EaseCollectionViewCell @end
@interface EaseUICollectionReusableView_ : EaseCollectionReusableView @end
@interface EaseUICollectionViewLayout_ : EaseCollectionViewLayout @end
@interface EaseUICollectionViewFlowLayout_ : EaseCollectionViewFlowLayout @end
@protocol EaseUICollectionViewDelegateFlowLayout_ <EaseCollectionViewDelegateFlowLayout> @end
@interface EaseUICollectionViewLayoutAttributes_ : EaseCollectionViewLayoutAttributes @end
@interface EaseUICollectionViewController_ : EaseCollectionViewController <EaseUICollectionViewDelegate, EaseUICollectionViewDataSource> @end
